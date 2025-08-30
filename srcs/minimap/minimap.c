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

// void	draw_minimap(t_game *game)
// {
// 	int		tile;
// 	int		offx;
// 	int		offy;
// 	int		i;
// 	int		j;
// 	int		w;
// 	int		h;

// 	if (!game || !game->map || !game->mlx.img.data)
// 		return ;
// 	tile = minimap_tile_size(game);
// 	offx = 8;
// 	offy = 8;
// 	w = game->map_width * tile;
// 	h = game->map_height * tile;
// 	draw_rect(&game->mlx.img, offx - 1, offy - 1, w + 2, h + 2, 0x0F0F12);
// 	draw_border(&game->mlx.img, offx - 1, offy - 1, w + 2, h + 2, MM_BORDER);
// 	i = 0;
// 	while (i < game->map_height)
// 	{
// 		j = 0;
// 		while (j < game->map_width)
// 		{
// 			if (game->map[i][j] == '1')
// 				draw_rect(&game->mlx.img, offx + j * tile, offy + i * tile,
// 					tile, tile, MM_WALL);
// 			else if (game->map[i][j] != '\0')
// 				draw_rect(&game->mlx.img, offx + j * tile, offy + i * tile,
// 					tile, tile, MM_FLOOR);
// 			j++;
// 		}
// 		i++;
// 	}
// 	{
// 		int px = offx + (int)(game->player.x * (double)tile);
// 		int py = offy + (int)(game->player.y * (double)tile);
// 		int ps;
// 		if (tile >= 6)
// 			ps = 4;
// 		else
// 			ps = 2;
// 		draw_rect(&game->mlx.img, px - ps / 2, py - ps / 2, ps, ps, MM_PLAYER);
// 		{
// 			int len = tile * 2;
// 			int lx = px + (int)(game->player.dir_x * (double)len);
// 			int ly = py + (int)(game->player.dir_y * (double)len);
// 			draw_line(&game->mlx.img, px, py, lx, ly, MM_PLAYER);
// 		}
// 	}
// }

// ==================== 玩家位置绘制 ====================

// 21. 计算玩家屏幕位置
void calculate_player_screen_pos(t_game *game, int *px, int *py)
{
    *px = game->minimap.offset_x + 
        (int)(game->player.x * (double)game->minimap.tile_size);
    *py = game->minimap.offset_y + 
        (int)(game->player.y * (double)game->minimap.tile_size);
}

// 22. 绘制玩家标记
void draw_player_marker(t_game *game)
{
    t_rect_params player_rect;
    int px;
    int py;
    
    calculate_player_screen_pos(game, &px, &py);
    player_rect.x = px - game->minimap.player_size / 2;
    player_rect.y = py - game->minimap.player_size / 2;
    player_rect.width = game->minimap.player_size;
    player_rect.height = game->minimap.player_size;
    player_rect.color = MM_PLAYER;
    draw_rect(&game->mlx.img, player_rect);
}

// 23. 绘制玩家方向线
void draw_player_direction(t_game *game)
{
    t_line_params dir_line;
    int px;
    int py;
    int len;
    
    calculate_player_screen_pos(game, &px, &py);
    len = game->minimap.tile_size * 2;
    dir_line.x0 = px;
    dir_line.y0 = py;
    dir_line.x1 = px + (int)(game->player.dir_x * (double)len);
    dir_line.y1 = py + (int)(game->player.dir_y * (double)len);
    dir_line.color = MM_PLAYER;
    draw_line(&game->mlx.img, dir_line);
}

// 24. 绘制完整minimap主函数
void draw_minimap(t_game *game)
{
    if (!game || !game->map || !game->mlx.img.data)
        return ;
    init_minimap_params(game);
    draw_minimap_background(game);
    draw_map_tiles(game);
    draw_player_marker(game);
    draw_player_direction(game);
}



