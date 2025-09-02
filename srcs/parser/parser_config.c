/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclee <niclee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:47:03 by niclee            #+#    #+#             */
/*   Updated: 2025/09/02 15:47:03 by niclee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	parse_config(char *line, t_parse *parser)
{
	if (is_texture(line))
		return (parse_texture(line, parser));
	else if (is_color(line))
		return (parse_color(line, parser));
	return (0);
}

int	parse_rgb_values(const char *rgb_str, int *r, int *g, int *b)
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
	char	*rgb_str;
	int		r;
	int		g;
	int		b;

	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (parser->got_f)
			return (0);
		rgb_str = trim_whitespace(line + 2);
		if (!parse_rgb_values(rgb_str, &r, &g, &b))
			return (free(rgb_str), 0);
		parser->textures->floor_r = r;
		parser->textures->floor_g = g;
		parser->textures->floor_b = b;
		parser->textures->floor_color = (r << 16) | (g << 8) | b;
		parser->got_f = 1;
		free(rgb_str);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (parser->got_c)
			return (0);
		rgb_str = trim_whitespace(line + 2);
		if (!parse_rgb_values(rgb_str, &r, &g, &b))
			return (free(rgb_str), 0);
		parser->textures->ceiling_r = r;
		parser->textures->ceiling_g = g;
		parser->textures->ceiling_b = b;
		parser->textures->ceiling_color = (r << 16) | (g << 8) | b;
		parser->got_c = 1;
		free(rgb_str);
	}
	return (1);
}
