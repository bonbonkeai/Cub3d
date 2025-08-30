/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:34:31 by jdu               #+#    #+#             */
/*   Updated: 2025/08/26 16:34:32 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// 5. DDA算法执行一步
void dda_step(t_game *game)
{
    if (game->ray.side_dist_x < game->ray.side_dist_y)
    {
        game->ray.side_dist_x += game->ray.delta_dist_x;
        game->ray.map_x += game->ray.step_x;
        game->ray.side = 0;
    }
    else
    {
        game->ray.side_dist_y += game->ray.delta_dist_y;
        game->ray.map_y += game->ray.step_y;
        game->ray.side = 1;
    }
}

// 6. DDA算法寻找墙壁
void perform_dda(t_game *game)
{
    int hit;
    
    hit = 0;
    while (hit == 0)
    {
        dda_step(game);
        if (game->map[game->ray.map_y][game->ray.map_x] == '1')
            hit = 1;
    }
}

// 7. 计算垂直墙距
void calculate_perp_wall_dist(t_game *game)
{
    if (game->ray.side == 0)
        game->temp_perp_dist = (game->ray.map_x - game->player.x 
            + (1 - game->ray.step_x) / 2) / game->ray.ray_dir_x;
    else
        game->temp_perp_dist = (game->ray.map_y - game->player.y 
            + (1 - game->ray.step_y) / 2) / game->ray.ray_dir_y;
}

// 8. 计算绘制范围
void calculate_draw_range(t_game *game)
{
    game->draw.line_height = (int)(game->win_height / game->temp_perp_dist);
    game->draw.draw_start = -game->draw.line_height / 2 + game->win_height / 2;
    if (game->draw.draw_start < 0)
        game->draw.draw_start = 0;
    game->draw.draw_end = game->draw.line_height / 2 + game->win_height / 2;
    if (game->draw.draw_end >= game->win_height)
        game->draw.draw_end = game->win_height - 1;
}

