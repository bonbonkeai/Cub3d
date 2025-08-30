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

// 15. 初始化minimap参数
void init_minimap_params(t_game *game)
{
    game->minimap.tile_size = minimap_tile_size(game);
    game->minimap.offset_x = 8;
    game->minimap.offset_y = 8;
    game->minimap.total_width = game->map_width * game->minimap.tile_size;
    game->minimap.total_height = game->map_height * game->minimap.tile_size;
    if (game->minimap.tile_size >= 6)
        game->minimap.player_size = 4;
    else
        game->minimap.player_size = 2;
}

// ==================== Minimap背景绘制 ====================

// 16. 绘制minimap背景
void draw_minimap_background(t_game *game)
{
    t_rect_params bg_rect;
    t_rect_params border_rect;
    
    bg_rect.x = game->minimap.offset_x - 1;
    bg_rect.y = game->minimap.offset_y - 1;
    bg_rect.width = game->minimap.total_width + 2;
    bg_rect.height = game->minimap.total_height + 2;
    bg_rect.color = 0x0F0F12;
    draw_rect(&game->mlx.img, bg_rect);
    border_rect = bg_rect;
    border_rect.color = MM_BORDER;
    draw_border(&game->mlx.img, border_rect);
}