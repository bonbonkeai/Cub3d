/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:36:15 by niclee            #+#    #+#             */
/*   Updated: 2025/08/28 00:48:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*MAIN FUNCTION FOR THE PARSING*/

int	parse_file(const char *filepath, t_game *game)
{
	t_parse	parser;
	char	*line;
	int		fd;

	init_parser(&parser); // initialisation
	fd = open(filepath, O_RDONLY);
	line = get_next_line(fd);
	if (fd < 0)
		return (error_msg("Cannot open file"));
	while (line) // read line by line
	{
		line = trim_whitespace(line); // skip whitespace
		if (is_empty_line(line)) // skip empty line
			continue ;
		if (!parser.map_started)
		{
			if (is_texture(line) || is_color(line)) // if correct texture and color
			{
				if (!parse_config(line, &parser)) // parse config (color and texture)
					return (ft_free(&parser, fd)); // if not correct free everything
			}
			else if (is_map_line(line)) // if correct
				parser.map_started = 1; // setup the map
		}
		else
		{
			if (!append_line(&parser.raw_lines, &parser.raw_count, line)) // parse the map
				return (ft_free(&parser, fd));
		}
	}
	// check if all valid
	if (!char_valid(&parser))
		return (ft_free(&parser, fd));
	if (!validate_and_process_map(&parser, game)) // check if map is closed and has 1 player
		return (ft_free(&parser, fd));
	save_data(&parser, game); // save the data to game
	close(fd);
	return (1);
}

int	parse_config(char *line, t_parse *parser) 
{
	if (is_texture(line))
		return (parse_texture(line, parser));
	else if (is_color(line))
		return (parse_color(line, parser));
	return (0);
}

int	parse_rgb_values(const char *rgb_str, int *r, int *g, int *b) /*check if we have a valid values for colors*/
{
	char	**split;
	int		i;

	split = ft_split(rgb_str, ',');
	if (!split)
		return (0);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
	{
		ft_free_array(split);
		return (0);
	}
	*r = ft_atoi(split[0]);
	*g = ft_atoi(split[1]);
	*b = ft_atoi(split[2]);
	ft_free_array(split);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (0);
	return (1);
}

int	parse_color(char *line, t_parse *parser)
{
	
}

// int main(void) // TESTING PARSING
