/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:34:23 by jdu               #+#    #+#             */
/*   Updated: 2025/08/26 16:34:25 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// 计算射线方向的增量距离
void	calculate_delta_dist(double ray_dir_x, double ray_dir_y, 
						double *delta_dist_x, double *delta_dist_y)
{
	if (fabs(ray_dir_x) < 1e-10)
		*delta_dist_x = 1e30;
	else
		*delta_dist_x = fabs(1.0 / ray_dir_x);
	if (fabs(ray_dir_y) < 1e-10)
		*delta_dist_y = 1e30;
	else
		*delta_dist_y = fabs(1.0 / ray_dir_y);
}

// 计算垂直墙距
double	calculate_perp_wall_dist(double ray_dir_x, double ray_dir_y,
							t_game *game, t_ray_data *ray)
{
	double	perp_wall_dist;

	if (ray->side == 0)
	{
		perp_wall_dist = (ray->map_x - game->player.x 
			+ (1 - ray->step_x) / 2) / ray_dir_x;
	}
	else
	{
		perp_wall_dist = (ray->map_y - game->player.y 
			+ (1 - ray->step_y) / 2) / ray_dir_y;
	}
	return (perp_wall_dist);
}

// 计算绘制参数
void	calculate_draw_params(t_game *game, double perp_wall_dist,
						t_draw_data *draw)
{
	draw->line_height = (int)(game->win_height / perp_wall_dist);
	draw->draw_start = -draw->line_height / 2 + game->win_height / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + game->win_height / 2;
	if (draw->draw_end >= game->win_height)
		draw->draw_end = game->win_height - 1;
}

// 计算墙壁命中点
double	calculate_wall_x(double ray_dir_x, double ray_dir_y,
					t_game *game, t_ray_data *ray, double perp_wall_dist)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.y + perp_wall_dist * ray_dir_y;
	else
		wall_x = game->player.x + perp_wall_dist * ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

// 计算纹理X坐标
int	calculate_tex_x(double wall_x, t_img *tex, double ray_dir_x,
				double ray_dir_y, int side)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)tex->width);
	if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}
