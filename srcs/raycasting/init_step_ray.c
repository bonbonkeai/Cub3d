/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_step_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:34:57 by jdu               #+#    #+#             */
/*   Updated: 2025/08/26 16:34:58 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// 初始化步长和边距 - X方向
void	init_step_x(double ray_dir_x, double player_x, 
				int map_x, t_ray_data *ray)
{
	if (ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player_x - map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (map_x + 1.0 - player_x) * ray->delta_dist_x;
	}
}

// 初始化步长和边距 - Y方向
void	init_step_y(double ray_dir_y, double player_y, 
				int map_y, t_ray_data *ray)
{
	if (ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player_y - map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (map_y + 1.0 - player_y) * ray->delta_dist_y;
	}
}

// 初始化射线数据
void	init_ray_data(t_game *game, double camera_x, t_ray_data *ray)
{
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	calculate_delta_dist(ray->ray_dir_x, ray->ray_dir_y,
		&ray->delta_dist_x, &ray->delta_dist_y);
}
