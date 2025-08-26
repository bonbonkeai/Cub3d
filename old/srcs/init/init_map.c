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

int	init_map(t_game *game, const char *filepath)
{
	int		fd;
	char	*line;
	char	**raw_lines;
	int		map_start;
	int		line_count;
	int		capacity;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (0);
	capacity = 32;
	raw_lines = malloc(sizeof(char *) * capacity);
	if (!raw_lines)
		return (0);
	map_start = 0;
	line_count = 0;
	while ((line = get_next_line(fd)))
	{
		if (!map_start && is_map_line(line))
			map_start = 1;
		if (map_start)
		{
			char *trimmed = ft_strtrim(line, "\n");
			free(line);
			if (!trimmed || !append_line(&raw_lines, &line_count, trimmed))
			{
				free(line);
				close(fd);
				return (0);
			}
		}
		else
			free(line);
	}
	close(fd);
	raw_lines[line_count] = NULL;
	if (line_count == 0)
		return (0);
	return (normalize_map(game, raw_lines, line_count));
}
