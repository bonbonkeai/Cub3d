/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:11:40 by jdu               #+#    #+#             */
/*   Updated: 2025/08/30 13:11:43 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../cub3d.h"

// 1. 初始化射线数据
void init_ray_for_column(t_game *game, int x)
{
    double camera_x;
    
    camera_x = 2 * x / (double)game->win_width - 1;
    game->ray.ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
    game->ray.ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
    game->ray.map_x = (int)game->player.x;
    game->ray.map_y = (int)game->player.y;
}

// 2. 计算增量距离
void calculate_delta_distances(t_game *game)
{
    if (fabs(game->ray.ray_dir_x) < 1e-10)
        game->ray.delta_dist_x = 1e30;
    else
        game->ray.delta_dist_x = fabs(1.0 / game->ray.ray_dir_x);
        
    if (fabs(game->ray.ray_dir_y) < 1e-10)
        game->ray.delta_dist_y = 1e30;
    else
        game->ray.delta_dist_y = fabs(1.0 / game->ray.ray_dir_y);
}

// 3. 计算X方向步长
void calculate_step_x(t_game *game)
{
    if (game->ray.ray_dir_x < 0)
    {
        game->ray.step_x = -1;
        game->ray.side_dist_x = (game->player.x - game->ray.map_x) * game->ray.delta_dist_x;
    }
    else
    {
        game->ray.step_x = 1;
        game->ray.side_dist_x = (game->ray.map_x + 1.0 - game->player.x) * game->ray.delta_dist_x;
    }
}

// 4. 计算Y方向步长
void calculate_step_y(t_game *game)
{
    if (game->ray.ray_dir_y < 0)
    {
        game->ray.step_y = -1;
        game->ray.side_dist_y = (game->player.y - game->ray.map_y) * game->ray.delta_dist_y;
    }
    else
    {
        game->ray.step_y = 1;
        game->ray.side_dist_y = (game->ray.map_y + 1.0 - game->player.y) * game->ray.delta_dist_y;
    }
}
