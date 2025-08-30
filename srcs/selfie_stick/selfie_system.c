/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selfie_system.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:10:55 by jdu               #+#    #+#             */
/*   Updated: 2025/08/30 15:04:04 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// 绘制单个像素（含透明判断）
static void	draw_selfie_pixel(t_game *game, int dst_x, int dst_y, int color)
{
	int	alpha;

	alpha = (color >> 24) & 0xFF;
	if (alpha == 0)
		put_px(&game->mlx.img, dst_x, dst_y, color);
}

// 获取源像素
static int	get_selfie_pixel(t_img *img, int x, int y)
{
	char	*src;
	int		color;

	src = img->data + y * img->size_line + x * (img->bpp / 8);
	color = *(int *)src;
	return (color);
}

// 遍历纹理
static void	draw_selfie_row(t_game *game, int y)
{
	int	x;
	int	dst_x;
	int	dst_y;
	int	color;

	x = 0;
	while (x < game->selfie_cam.selfie_texture->width)
	{
		dst_x = game->selfie_cam.x_pos + x;
		dst_y = game->selfie_cam.y_pos + y;
		if (dst_x >= 0 && dst_x < game->win_width && \
			dst_y >= 0 && dst_y < game->win_height)
		{
			color = get_selfie_pixel(game->selfie_cam.selfie_texture, x, y);
			draw_selfie_pixel(game, dst_x, dst_y, color);
		}
		x++;
	}
}

void	draw_static_selfie_stick(t_game *game)
{
	int	y;

	if (!game->selfie_cam.visible || !game->selfie_cam.selfie_texture)
		return ;
	y = 0;
	while (y < game->selfie_cam.selfie_texture->height)
	{
		draw_selfie_row(game, y);
		y++;
	}
}
