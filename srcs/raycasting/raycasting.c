/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:35:11 by jdu               #+#    #+#             */
/*   Updated: 2025/08/26 16:35:14 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// void	cast_rays(t_game *game)
// {
// 	int		x;

// 	x = 0;
// 	while (x < game->win_width)
// 	{
// 		// 计算当前射线在相机平面上的位置 (-1 ~ 1)
// 		double	camera_x = 2 * x / (double)game->win_width - 1;
// 		double	ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
// 		double	ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;

// 		int		map_x = (int)game->player.x;
// 		int		map_y = (int)game->player.y;

// 		double	delta_dist_x;
// 		if (fabs(ray_dir_x) < 1e-10)
// 			delta_dist_x = 1e30;
// 		else
// 			delta_dist_x = fabs(1.0 / ray_dir_x);

// 		double	delta_dist_y;
// 		if (fabs(ray_dir_y) < 1e-10)
// 			delta_dist_y = 1e30;
// 		else
// 			delta_dist_y = fabs(1.0 / ray_dir_y);
		
// 		double	side_dist_x;
// 		double	side_dist_y;
// 		int		step_x;
// 		int		step_y;
// 		int		hit = 0;
// 		int		side;

// 		// 初始化步长和初始边距
// 		if (ray_dir_x < 0)
// 		{
// 			step_x = -1;
// 			side_dist_x = (game->player.x - map_x) * delta_dist_x;
// 		}
// 		else
// 		{
// 			step_x = 1;
// 			side_dist_x = (map_x + 1.0 - game->player.x) * delta_dist_x;
// 		}
// 		if (ray_dir_y < 0)
// 		{
// 			step_y = -1;
// 			side_dist_y = (game->player.y - map_y) * delta_dist_y;
// 		}
// 		else
// 		{
// 			step_y = 1;
// 			side_dist_y = (map_y + 1.0 - game->player.y) * delta_dist_y;
// 		}

// 		// DDA 算法寻找墙壁
// 		while (hit == 0)
// 		{
// 			if (side_dist_x < side_dist_y)
// 			{
// 				side_dist_x += delta_dist_x;
// 				map_x += step_x;
// 				side = 0;
// 			}
// 			else
// 			{
// 				side_dist_y += delta_dist_y;
// 				map_y += step_y;
// 				side = 1;
// 			}
// 			if (game->map[map_y][map_x] == '1')
// 				hit = 1;
// 		}

// 		// 计算到墙的垂直距离
// 		double	perp_wall_dist;
// 		if (side == 0)
// 			perp_wall_dist = (map_x - game->player.x + (1 - step_x) / 2) / ray_dir_x;
// 		else
// 			perp_wall_dist = (map_y - game->player.y + (1 - step_y) / 2) / ray_dir_y;

// 		// 计算绘制的垂直线高度
// 		int line_height = (int)(game->win_height / perp_wall_dist);
// 		int draw_start = -line_height / 2 + game->win_height / 2;
// 		if (draw_start < 0)
// 			draw_start = 0;
// 		int draw_end = line_height / 2 + game->win_height / 2;
// 		if (draw_end >= game->win_height)
// 			draw_end = game->win_height - 1;

// 		// 确定使用的纹理
// 		t_img	*tex;
// 		if (side == 0 && ray_dir_x > 0)
// 			tex = &game->textures.we; // 西
// 		else if (side == 0 && ray_dir_x < 0)
// 			tex = &game->textures.ea; // 东
// 		else if (side == 1 && ray_dir_y > 0)
// 			tex = &game->textures.no; // 北
// 		else
// 			tex = &game->textures.so; // 南

// 		// 计算墙壁命中点的精确位置
// 		double	wall_x;
// 		if (side == 0)
// 			wall_x = game->player.y + perp_wall_dist * ray_dir_y;
// 		else
// 			wall_x = game->player.x + perp_wall_dist * ray_dir_x;
// 		wall_x -= floor(wall_x);

// 		//计算纹理 X 坐标（安全取模）
// 		int	tex_x = (int)(wall_x * (double)tex->width);
// 		if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
// 			tex_x = tex->width - tex_x - 1;
// 		if (tex_x < 0)
// 			tex_x = 0;
// 		else if (tex_x >= tex->width)
// 			tex_x = tex->width - 1;

// 		//计算纹理 Y 步长
// 		double	step = 1.0 * tex->height / line_height;
// 		double	tex_pos = (draw_start - game->win_height / 2 + line_height / 2) * step;

// 		//画天花板
// 		int	y = 0;
// 		while (y < draw_start)
// 			put_px(&game->mlx.img, x, y++, game->textures.ceiling_color);

// 		//画墙面
// 		while (y < draw_end)
//         {
//             int tex_y = (int)tex_pos % tex->height;
//             if (tex_y < 0)
//                 tex_y += tex->height;
//             tex_pos += step;
//             char *pixel = tex->data + (tex_y * tex->size_line + tex_x * (tex->bpp / 8));
//             int color = *(int *)pixel;
//             if (side == 1)
//             {
//                 unsigned char r = (unsigned char)((color >> 16) & 0xFF);
//                 unsigned char g = (unsigned char)((color >> 8) & 0xFF);
//                 unsigned char b = (unsigned char)(color & 0xFF);
//                 color = (r << 16) | (g << 8) | b;
//             }
//             put_px(&game->mlx.img, x, y, color);
//             y++;
//         }
// 		// 画地板
// 		while (y < game->win_height)
// 			put_px(&game->mlx.img, x, y++, game->textures.floor_color);

// 		x++;
// 	}
// }

void	put_px(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->data)
		return ;
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(int *)dst = color;
}

// 18. 主raycasting函数
void cast_rays(t_game *game)
{
	int x;
	
	x = 0;
	while (x < game->win_width)
	{
		init_ray_for_column(game, x);
		calculate_delta_distances(game);
		calculate_step_x(game);
		calculate_step_y(game);
		perform_dda(game);
		calculate_perp_wall_dist(game);
		calculate_draw_range(game);
		select_wall_texture(game);
		calculate_wall_hit(game);
		calculate_tex_x(game);
		calculate_texture_step(game);
		draw_column(game, x);
		x++;
	}
}

// 28. 初始化游戏结构体
void init_game_structs(t_game *game)
{
	game->crosshair.size = 3;
	game->crosshair.line_len = 15;
	game->crosshair.gap = 8;
	game->crosshair.color = 0x00FF00;
	game->crosshair.alpha = 200;
	game->temp_perp_dist = 0.0;
	game->temp_wall_x = 0.0;
}

void	init_ray(t_game *game)
{
	game->ray.ray_dir_x = 0.0;
	game->ray.ray_dir_y = 0.0;
	game->ray.map_x = 0;
	game->ray.map_y = 0;
	game->ray.delta_dist_x = 0.0;
	game->ray.delta_dist_y = 0.0;
	game->ray.side_dist_x = 0.0;
	game->ray.side_dist_y = 0.0;
	game->ray.step_x = 0;
	game->ray.step_y = 0;
	game->ray.side = 0;
}

void init_game_structures(t_game *game)
{
	init_game_structs(game);
	init_ray(game);
	// 初始化绘制参数结构体
	game->draw.line_height = 0;
	game->draw.draw_start = 0;
	game->draw.draw_end = 0;
	// 初始化墙面参数结构体
	game->wall_params.tex = NULL;
	game->wall_params.tex_x = 0;
	game->wall_params.step = 0.0;
	game->wall_params.tex_pos = 0.0;
	//初始化minimap
	game->minimap.tile_size = 0;
    game->minimap.offset_x = 8;
    game->minimap.offset_y = 8;
    game->minimap.total_width = 0;
    game->minimap.total_height = 0;
    game->minimap.player_size = 0;
}