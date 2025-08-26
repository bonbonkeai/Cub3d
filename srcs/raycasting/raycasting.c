#include "../../cub3d.h"

void	cast_rays(t_game *game)
{
	int		x;

	x = 0;
	while (x < game->win_width)
	{
		// 计算当前射线在相机平面上的位置 (-1 ~ 1)
		double	camera_x = 2 * x / (double)game->win_width - 1;
		double	ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
		double	ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;

		int		map_x = (int)game->player.x;
		int		map_y = (int)game->player.y;

		double	delta_dist_x;
		if (fabs(ray_dir_x) < 1e-10)
			delta_dist_x = 1e30;
		else
			delta_dist_x = fabs(1.0 / ray_dir_x);

		double	delta_dist_y;
		if (fabs(ray_dir_y) < 1e-10)
			delta_dist_y = 1e30;
		else
			delta_dist_y = fabs(1.0 / ray_dir_x);
		
		double	side_dist_x;
		double	side_dist_y;
		int		step_x;
		int		step_y;
		int		hit = 0;
		int		side;

		// 初始化步长和初始边距
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (game->player.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - game->player.x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (game->player.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - game->player.y) * delta_dist_y;
		}

		// DDA 算法寻找墙壁
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (game->map[map_y][map_x] == '1')
				hit = 1;
		}

		// 计算到墙的垂直距离
		double	perp_wall_dist;
		if (side == 0)
			perp_wall_dist = (map_x - game->player.x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - game->player.y + (1 - step_y) / 2) / ray_dir_y;

		// 计算绘制的垂直线高度
		int line_height = (int)(game->win_height / perp_wall_dist);
		int draw_start = -line_height / 2 + game->win_height / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + game->win_height / 2;
		if (draw_end >= game->win_height)
			draw_end = game->win_height - 1;

		// 确定使用的纹理
		t_img	*tex;
		if (side == 0 && ray_dir_x > 0)
			tex = &game->textures.we; // 西
		else if (side == 0 && ray_dir_x < 0)
			tex = &game->textures.ea; // 东
		else if (side == 1 && ray_dir_y > 0)
			tex = &game->textures.no; // 北
		else
			tex = &game->textures.so; // 南

		// 计算墙壁命中点的精确位置
		double	wall_x;
		if (side == 0)
			wall_x = game->player.y + perp_wall_dist * ray_dir_y;
		else
			wall_x = game->player.x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);

		//计算纹理 X 坐标（安全取模）
		int	tex_x = (int)(wall_x * (double)tex->width);
		if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
			tex_x = tex->width - tex_x - 1;
		if (tex_x < 0)
			tex_x = 0;
		else if (tex_x >= tex->width)
			tex_x = tex->width - 1;

		//计算纹理 Y 步长
		double	step = 1.0 * tex->height / line_height;
		double	tex_pos = (draw_start - game->win_height / 2 + line_height / 2) * step;

		//画天花板
		int	y = 0;
		while (y < draw_start)
			put_px(&game->mlx.img, x, y++, game->textures.ceiling_color);

		//画墙面
		while (y < draw_end)
        {
            int tex_y = (int)tex_pos % tex->height;
            if (tex_y < 0)
                tex_y += tex->height;
            tex_pos += step;
            char *pixel = tex->data + (tex_y * tex->size_line + tex_x * (tex->bpp / 8));
            int color = *(int *)pixel;
            if (side == 1)
            {
                unsigned char r = (unsigned char)((color >> 16) & 0xFF);
                unsigned char g = (unsigned char)((color >> 8) & 0xFF);
                unsigned char b = (unsigned char)(color & 0xFF);
                color = (r << 16) | (g << 8) | b;
            }
            put_px(&game->mlx.img, x, y, color);
            y++;
        }
		// 画地板
		while (y < game->win_height)
			put_px(&game->mlx.img, x, y++, game->textures.floor_color);

		x++;
	}
}