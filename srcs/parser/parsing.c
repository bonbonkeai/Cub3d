/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclee <niclee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:36:15 by niclee            #+#    #+#             */
/*   Updated: 2025/08/26 15:14:02 by niclee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
				if (!parse_config(line, &parser)) // parse config
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
	
}

// int main(void) // TESTING PARSING