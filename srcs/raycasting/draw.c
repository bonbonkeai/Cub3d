/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:34:40 by jdu               #+#    #+#             */
/*   Updated: 2025/08/26 16:34:42 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// 选择纹理
t_img	*select_texture(t_game *game, double ray_dir_x, 
					double ray_dir_y, int side)
{
	if (side == 0 && ray_dir_x > 0)
		return (&game->textures.we);
	else if (side == 0 && ray_dir_x < 0)
		return (&game->textures.ea);
	else if (side == 1 && ray_dir_y > 0)
		return (&game->textures.no);
	else
		return (&game->textures.so);
}


// 绘制天花板
void	draw_ceiling(t_game *game, int x, int draw_start)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		put_px(&game->mlx.img, x, y, game->textures.ceiling_color);
		y++;
	}
}

// 应用侧面阴影效果
int	apply_side_shading(int color, int side)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	if (side == 1)
	{
		r = (unsigned char)((color >> 16) & 0xFF);
		g = (unsigned char)((color >> 8) & 0xFF);
		b = (unsigned char)(color & 0xFF);
		return ((r << 16) | (g << 8) | b);
	}
	return (color);
}

// 绘制墙面
void	draw_wall(t_game *game, t_wall_draw_params *params)
{
	int		tex_y;
	char	*pixel;
	int		color;

	while (params->y < params->draw_end)
	{
		tex_y = (int)params->tex_pos % params->tex->height;
		if (tex_y < 0)
			tex_y += params->tex->height;
		params->tex_pos += params->step;
		pixel = params->tex->data + (tex_y * params->tex->size_line
			+ params->tex_x * (params->tex->bpp / 8));
		color = *(int *)pixel;
		color = apply_side_shading(color, params->side);
		put_px(&game->mlx.img, params->x, params->y, color);
		params->y++;
	}
}

// 绘制地板
void	draw_floor(t_game *game, int x, int y)
{
	while (y < game->win_height)
	{
		put_px(&game->mlx.img, x, y, game->textures.floor_color);
		y++;
	}
}
