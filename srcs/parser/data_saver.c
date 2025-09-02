/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_saver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclee <niclee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:47:06 by niclee            #+#    #+#             */
/*   Updated: 2025/09/02 15:47:06 by niclee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	save_data(t_parse *parser, t_game *game)
{
	if (!parser->textures)
		return ;
	game->textures.no_path = parser->textures->no_path;
	game->textures.so_path = parser->textures->so_path;
	game->textures.we_path = parser->textures->we_path;
	game->textures.ea_path = parser->textures->ea_path;
	game->textures.floor_color = parser->textures->floor_color;
	game->textures.ceiling_color = parser->textures->ceiling_color;
	game->textures.floor_r = parser->textures->floor_r;
	game->textures.floor_g = parser->textures->floor_g;
	game->textures.floor_b = parser->textures->floor_b;
	game->textures.ceiling_r = parser->textures->ceiling_r;
	game->textures.ceiling_g = parser->textures->ceiling_g;
	game->textures.ceiling_b = parser->textures->ceiling_b;
	parser->textures->no_path = NULL;
	parser->textures->so_path = NULL;
	parser->textures->we_path = NULL;
	parser->textures->ea_path = NULL;
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
}

void	cleanup_get_next_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}
