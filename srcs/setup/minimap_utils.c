/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:59:05 by jdu               #+#    #+#             */
/*   Updated: 2025/08/27 13:59:07 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	draw_rect(t_img *img, int x, int y, int w, int h, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			put_px(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

int	minimap_tile_size(t_game *g)
{
	int	max_w;
	int	max_h;
	int	tw;
	int	th;
	int	tile;

	max_w = g->win_width / 3;
	max_h = g->win_height / 3;
	if (g->map_width <= 0 || g->map_height <= 0)
		return (4);
	tw = max_w / g->map_width;
	th = max_h / g->map_height;
	tile = tw;
	if (th < tile)
		tile = th;
	if (tile < 2)
		tile = 2;
	return (tile);
}

void	draw_border(t_img *img, int x, int y, int w, int h, int color)
{
	int	i;

	i = 0;
	while (i < w)
	{
		put_px(img, x + i, y, color);
		put_px(img, x + i, y + h - 1, color);
		i++;
	}
	i = 0;
	while (i < h)
	{
		put_px(img, x, y + i, color);
		put_px(img, x + w - 1, y + i, color);
		i++;
	}
}
