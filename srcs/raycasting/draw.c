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

// 13. 绘制天花板
void draw_ceiling(t_game *game, int x)
{
    int y;
    
    y = 0;
    while (y < game->draw.draw_start)
    {
        put_px(&game->mlx.img, x, y, game->textures.ceiling_color);
        y++;
    }
}

// 14. 应用侧面阴影
int apply_side_shading(int color, int side)
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    
    if (side == 1)
    {
        r = (unsigned char)((color >> 16) & 0xFF);
        g = (unsigned char)((color >> 8) & 0xFF);
        b = (unsigned char)(color & 0xFF);
        return ((r << 16) | (g << 8) | b);
    }
    return (color);
}

// 15. 绘制墙面
void draw_wall(t_game *game, int x)
{
    int y;
    int tex_y;
    char *pixel;
    int color;
    
    y = game->draw.draw_start;
    while (y < game->draw.draw_end)
    {
        tex_y = (int)game->wall_params.tex_pos % game->wall_params.tex->height;
        if (tex_y < 0)
            tex_y += game->wall_params.tex->height;
        game->wall_params.tex_pos += game->wall_params.step;
        pixel = game->wall_params.tex->data + (tex_y * game->wall_params.tex->size_line 
            + game->wall_params.tex_x * (game->wall_params.tex->bpp / 8));
        color = *(int *)pixel;
        color = apply_side_shading(color, game->ray.side);
        put_px(&game->mlx.img, x, y, color);
        y++;
    }
}

// 16. 绘制地板
void draw_floor(t_game *game, int x)
{
    int y;
    
    y = game->draw.draw_end;
    while (y < game->win_height)
    {
        put_px(&game->mlx.img, x, y, game->textures.floor_color);
        y++;
    }
}

// 17. 绘制单列
void draw_column(t_game *game, int x)
{
    draw_ceiling(game, x);
    draw_wall(game, x);
    draw_floor(game, x);
}
