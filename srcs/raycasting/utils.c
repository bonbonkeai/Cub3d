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

static void	put_px_alpha(t_img *img, int x, int y, int color, int alpha)
{
	char	*dst;
	int		r;
    int     g;
    int     b;
	int		bg_r;
    int     bg_g;
    int     bg_b;
	int		final_r;
    int     final_g;
    int     final_b;
	unsigned int	bg_color;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return;
	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	bg_color = *(unsigned int *)dst;
	// 提取前景色 RGB
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	// 提取背景色 RGB
	bg_r = (bg_color >> 16) & 0xFF;
	bg_g = (bg_color >> 8) & 0xFF;
	bg_b = bg_color & 0xFF;
	// alpha 混合公式：final = (fg*alpha + bg*(255-alpha)) / 255
	final_r = (r * alpha + bg_r * (255 - alpha)) / 255;
	final_g = (g * alpha + bg_g * (255 - alpha)) / 255;
	final_b = (b * alpha + bg_b * (255 - alpha)) / 255;

	*(unsigned int *)dst = (final_r << 16) | (final_g << 8) | final_b;
}


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
