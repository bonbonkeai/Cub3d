#include "cub3d.h"

// void	draw_crosshair(t_game *game)
// {
// 	int center_x = game->win_width / 2;
// 	int center_y = game->win_height / 2;
// 	int i;

// 	// 横线
// 	i = -CROSS_SIZE;
// 	while (i <= CROSS_SIZE)
// 	{
// 		put_px(&game->mlx.img, center_x + i, center_y, CROSS_COLOR);
// 		i++;
// 	}
// 	// 竖线
// 	i = -CROSS_SIZE;
// 	while (i <= CROSS_SIZE)
// 	{
// 		put_px(&game->mlx.img, center_x, center_y + i, CROSS_COLOR);
// 		i++;
// 	}
// }

void	draw_crosshair(t_game *game)
{
	int cx = game->win_width / 2;
	int cy = game->win_height / 2;
	int i, dx, dy;

	// 中心小圆点
	dy = -DOT_RADIUS;
	while (dy <= DOT_RADIUS)
	{
		dx = -DOT_RADIUS;
		while (dx <= DOT_RADIUS)
		{
			if (dx * dx + dy * dy <= DOT_RADIUS * DOT_RADIUS)
				put_px_alpha(&game->mlx.img, cx + dx, cy + dy, CROSS_COLOR, CROSS_ALPHA);
			dx++;
		}
		dy++;
	}

	// 上
	i = 0;
	while (i < LINE_LEN)
	{
		put_px_alpha(&game->mlx.img, cx, cy - GAP - i, CROSS_COLOR, CROSS_ALPHA);
		i++;
	}
	// 下
	i = 0;
	while (i < LINE_LEN)
	{
		put_px_alpha(&game->mlx.img, cx, cy + GAP + i, CROSS_COLOR, CROSS_ALPHA);
		i++;
	}
	// 左
	i = 0;
	while (i < LINE_LEN)
	{
		put_px_alpha(&game->mlx.img, cx - GAP - i, cy, CROSS_COLOR, CROSS_ALPHA);
		i++;
	}
	// 右
	i = 0;
	while (i < LINE_LEN)
	{
		put_px_alpha(&game->mlx.img, cx + GAP + i, cy, CROSS_COLOR, CROSS_ALPHA);
		i++;
	}
}
