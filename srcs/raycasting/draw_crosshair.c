/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_crosshair.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:34:49 by jdu               #+#    #+#             */
/*   Updated: 2025/08/26 16:34:51 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// 23. 绘制准星上线
void draw_crosshair_up(t_game *game)
{
    int cx;
    int cy;
    int i;
    t_pixel_params pixel;
    
    get_screen_center(game, &cx, &cy);
    init_crosshair_pixel(game, &pixel);
    pixel.x = cx;
    i = 0;
    while (i < game->crosshair.line_len)
    {
        pixel.y = cy - game->crosshair.gap - i;
        put_px_alpha(&game->mlx.img, pixel);
        i++;
    }
}

// 24. 绘制准星下线
void draw_crosshair_down(t_game *game)
{
    int cx;
    int cy;
    int i;
    t_pixel_params pixel;
    
    get_screen_center(game, &cx, &cy);
    init_crosshair_pixel(game, &pixel);
    pixel.x = cx;
    i = 0;
    while (i < game->crosshair.line_len)
    {
        pixel.y = cy + game->crosshair.gap + i;
        put_px_alpha(&game->mlx.img, pixel);
        i++;
    }
}

// 25. 绘制准星左线
void draw_crosshair_left(t_game *game)
{
    int cx;
    int cy;
    int i;
    t_pixel_params pixel;
    
    get_screen_center(game, &cx, &cy);
    init_crosshair_pixel(game, &pixel);
    pixel.y = cy;
    i = 0;
    while (i < game->crosshair.line_len)
    {
        pixel.x = cx - game->crosshair.gap - i;
        put_px_alpha(&game->mlx.img, pixel);
        i++;
    }
}

// 26. 绘制准星右线
void draw_crosshair_right(t_game *game)
{
    int cx;
    int cy;
    int i;
    t_pixel_params pixel;
    
    get_screen_center(game, &cx, &cy);
    init_crosshair_pixel(game, &pixel);
    pixel.y = cy;
    i = 0;
    while (i < game->crosshair.line_len)
    {
        pixel.x = cx + game->crosshair.gap + i;
        put_px_alpha(&game->mlx.img, pixel);
        i++;
    }
}

// 27. 绘制准星主函数
void draw_crosshair(t_game *game)
{
    draw_crosshair_center(game);
    draw_crosshair_up(game);
    draw_crosshair_down(game);
    draw_crosshair_left(game);
    draw_crosshair_right(game);
}