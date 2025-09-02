/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclee <niclee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:47:27 by niclee            #+#    #+#             */
/*   Updated: 2025/09/02 15:47:27 by niclee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	open_file(const char *filepath, t_parse *parser)
{
	int	fd;

	init_parser(parser);
	if (!parser->textures)
		return (error_msg("Memory allocation failed"));
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (ft_free_cub(parser, fd), error_msg("Cannot open file"));
	return (fd);
}

static int	handle_config_line(char *trimmed, t_parse *parser, int fd)
{
	if (is_texture(trimmed) || is_color(trimmed))
	{
		if (!parse_config(trimmed, parser))
		{
			free(trimmed);
			return (ft_free_cub(parser, fd));
		}
	}
	else if (is_map_line(trimmed))
	{
		parser->map_started = 1;
		if (!append_line(&parser->raw_lines, &parser->raw_count, trimmed))
			return (ft_free_cub(parser, fd));
	}
	else
		free(trimmed);
	return (1);
}

static int	process_line(char *line, t_parse *parser, int fd)
{
	char	*trimmed;

	trimmed = trim_whitespace(line);
	free(line);
	if (is_empty_line(trimmed))
		return (free(trimmed), 1);
	if (!parser->map_started)
	{
		if (!handle_config_line(trimmed, parser, fd))
			return (0);
	}
	else
	{
		if (!append_line(&parser->raw_lines, &parser->raw_count, trimmed))
			return (ft_free_cub(parser, fd));
	}
	if (!parser->map_started)
		free(trimmed);
	return (1);
}

static int	read_lines(int fd, t_parse *parser)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!process_line(line, parser, fd))
			return (0);
		line = get_next_line(fd);
	}
	return (1);
}

int	parse_file(const char *filepath, t_game *game)
{
	t_parse	parser;
	int		fd;

	fd = open_file(filepath, &parser);
	if (fd <= 0)
		return (0);
	if (!read_lines(fd, &parser))
		return (0);
	if (!char_valid(&parser))
		return (ft_free_cub(&parser, fd));
	if (!validate_and_process_map(&parser, game))
		return (ft_free_cub(&parser, fd));
	save_data(&parser, game);
	free(parser.textures);
	if (parser.raw_lines)
        free_raw_lines(parser.raw_lines, parser.raw_count);
	close(fd);
	return (1);
}
