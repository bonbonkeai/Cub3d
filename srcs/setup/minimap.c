/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:35:56 by jdu               #+#    #+#             */
/*   Updated: 2025/08/26 16:35:58 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	draw_minimap(t_game *game)
{
	int		tile;
	int		offx;
	int		offy;
	int		i;
	int		j;
	int		w;
	int		h;

	if (!game || !game->map || !game->mlx.img.data)
		return ;
	tile = minimap_tile_size(game);
	offx = 8;
	offy = 8;
	w = game->map_width * tile;
	h = game->map_height * tile;
	draw_rect(&game->mlx.img, offx - 1, offy - 1, w + 2, h + 2, 0x0F0F12);
	draw_border(&game->mlx.img, offx - 1, offy - 1, w + 2, h + 2, MM_BORDER);
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == '1')
				draw_rect(&game->mlx.img, offx + j * tile, offy + i * tile,
					tile, tile, MM_WALL);
			else if (game->map[i][j] != '\0')
				draw_rect(&game->mlx.img, offx + j * tile, offy + i * tile,
					tile, tile, MM_FLOOR);
			j++;
		}
		i++;
	}
	{
		int px = offx + (int)(game->player.x * (double)tile);
		int py = offy + (int)(game->player.y * (double)tile);
		int ps;
		if (tile >= 6)
			ps = 4;
		else
			ps = 2;
		draw_rect(&game->mlx.img, px - ps / 2, py - ps / 2, ps, ps, MM_PLAYER);
		{
			int len = tile * 2;
			int lx = px + (int)(game->player.dir_x * (double)len);
			int ly = py + (int)(game->player.dir_y * (double)len);
			draw_line(&game->mlx.img, px, py, lx, ly, MM_PLAYER);
		}
	}
}



