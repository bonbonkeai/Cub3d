/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:33:16 by jdu               #+#    #+#             */
/*   Updated: 2025/08/26 16:33:18 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_map_line(const char *line)
{
	if (!line)
		return (0);
	while (*line)
	{
		if (*line != '1' && *line != '0' && *line != 'N' &&
			*line != 'S' && *line != 'E' && *line != 'W' &&
			*line != ' ')
			return (0);
		line++;
	}
	return (1);
}

int	get_map_width(char **map)
{
	int	i;
	int	len;
	int	max_width;

	i = 0;
	max_width = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	normalize_map(t_game *game, char **raw_lines, int line_count)
{
	int		i;
	int		max_width;
	char	*new_line;
	int		len;

	max_width = get_map_width(raw_lines);
	i = 0;
	while (i < line_count)
	{
		new_line = malloc(max_width + 1);
		if (!new_line)
		{
			while (--i >= 0)
				free(raw_lines[i]);
			free(raw_lines);
			return (0);
		}
		ft_memset(new_line, ' ', max_width);
		new_line[max_width] = '\0';
		len = ft_strlen(raw_lines[i]);
		if (len > max_width)
			len = max_width;
		ft_memcpy(new_line, raw_lines[i], len);
		free(raw_lines[i]);
		raw_lines[i] = new_line;
		i++;
	}
	game->map = raw_lines;
	game->map_height = line_count;
	game->map_width = max_width;
	return (1);
}

int init_map(t_game *game, const char *filepath)
{
    int fd;
	char **raw_lines;
	int line_count;
	char *line;
	int map_start;
	char *trimmed;

	fd = open(filepath, O_RDONLY);
    if (fd < 0)
    {
        perror(filepath);
        return (0);
    }
    raw_lines = malloc(sizeof(char *) * 32);
    if (!raw_lines) 
	{
		close(fd);
		return 0;
	}
    line_count = 0;
    map_start = 0;
    while ((line = get_next_line(fd)))
    {
        trimmed = ft_strtrim(line, " \n\r\t");
        free(line);
        if (!trimmed) 
			continue ;
        if (!map_start)
        {
            if (is_map_line(trimmed))
                map_start = 1;
            else
            {
                free(trimmed);
                continue;
            }
        }
        if (!append_line(&raw_lines, &line_count, trimmed))
        {
            free(trimmed);
            close(fd);
            return (0);
        }
    }
    close(fd);
    if (line_count == 0) 
		return 0;
    raw_lines[line_count] = NULL;
    return (normalize_map(game, raw_lines, line_count));
}
