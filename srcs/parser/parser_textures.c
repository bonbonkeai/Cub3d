/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclee <niclee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:47:18 by niclee            #+#    #+#             */
/*   Updated: 2025/09/02 15:47:18 by niclee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	parse_north_texture(char *line, t_parse *parser)
{
	char	*path;

	if (parser->got_no)
		return (error_msg("Duplicate NORTH texture definition"));
	path = trim_whitespace(line + 3);
	if (!path || !*path)
	{
		if (path)
			free(path);
		return (error_msg("Empty NORTH texture path"));
	}
	if (!is_valid_texture_extension(path) || !is_file_accessible(path))
	{
		free(path);
		return (error_msg("Invalid NO texture: must be accessible .xpm file"));
	}
	parser->textures->no_path = path;
	parser->got_no = 1;
	return (1);
}

static int	parse_south_texture(char *line, t_parse *parser)
{
	char	*path;

	if (parser->got_so)
		return (error_msg("Duplicate SOUTH texture definition"));
	path = trim_whitespace(line + 3);
	if (!path || !*path)
	{
		if (path)
			free(path);
		return (error_msg("Empty SOUTH texture path"));
	}
	if (!is_valid_texture_extension(path) || !is_file_accessible(path))
	{
		free(path);
		return (error_msg("Invalid SO texture: must be accessible .xpm file"));
	}
	parser->textures->so_path = path;
	parser->got_so = 1;
	return (1);
}

static int	parse_west_texture(char *line, t_parse *parser)
{
	char	*path;

	if (parser->got_we)
		return (error_msg("Duplicate WEST texture definition"));
	path = trim_whitespace(line + 3);
	if (!path || !*path)
	{
		if (path)
			free(path);
		return (error_msg("Empty WEST texture path"));
	}
	if (!is_valid_texture_extension(path) || !is_file_accessible(path))
	{
		free(path);
		return (error_msg("Invalid WE texture: must be accessible .xpm file"));
	}
	parser->textures->we_path = path;
	parser->got_we = 1;
	return (1);
}

static int	parse_east_texture(char *line, t_parse *parser)
{
	char	*path;

	if (parser->got_ea)
		return (error_msg("Duplicate EAST texture definition"));
	path = trim_whitespace(line + 3);
	if (!path || !*path)
	{
		if (path)
			free(path);
		return (error_msg("Empty EAST texture path"));
	}
	if (!is_valid_texture_extension(path) || !is_file_accessible(path))
	{
		free(path);
		return (error_msg("Invalid EA texture: must be accessible .xpm file"));
	}
	parser->textures->ea_path = path;
	parser->got_ea = 1;
	return (1);
}

int	parse_texture(char *line, t_parse *parser)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_north_texture(line, parser));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_south_texture(line, parser));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_west_texture(line, parser));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_east_texture(line, parser));
	return (0);
}
