#include "../../cub3d.h"

static void put_px_alpha(t_img *img, int x, int y, int color, int alpha)
{
    char *dst;
    int r, g, b;
    int bg_r, bg_g, bg_b;
    int final_r, final_g, final_b;
    unsigned int bg_color;

    if (!img || !img->data)
        return;
    if (x < 0 || y < 0 || x >= img->width || y >= img->height)
        return;

    dst = img->data + (y * img->size_line + x * (img->bpp / 8));
    bg_color = *(unsigned int *)dst;

    // 提取前景色 RGB
    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;

    // 提取背景色 RGB
    bg_r = (bg_color >> 0) & 0xFF;
    bg_g = (bg_color >> 8) & 0xFF;
    bg_b = (bg_color >> 16) & 0xFF;

    // alpha 混合
    final_r = (r * alpha + bg_r * (255 - alpha)) / 255;
    final_g = (g * alpha + bg_g * (255 - alpha)) / 255;
    final_b = (b * alpha + bg_b * (255 - alpha)) / 255;

    *(unsigned int *)dst = (final_b << 16) | (final_g << 8) | final_r;
}

// void	draw_crosshair(t_game *game)
// {
// 	int cx = game->win_width / 2;
// 	int cy = game->win_height / 2;
// 	int i, dx, dy;

// 	// 中心小圆点
// 	dy = -DOT_RADIUS;
// 	while (dy <= DOT_RADIUS)
// 	{
// 		dx = -DOT_RADIUS;
// 		while (dx <= DOT_RADIUS)
// 		{
// 			if (dx * dx + dy * dy <= DOT_RADIUS * DOT_RADIUS)
// 				put_px_alpha(&game->mlx.img, cx + dx, cy + dy, CROSS_COLOR, CROSS_ALPHA);
// 			dx++;
// 		}
// 		dy++;
// 	}

// 	// 上
// 	i = 0;
// 	while (i < LINE_LEN)
// 	{
// 		put_px_alpha(&game->mlx.img, cx, cy - GAP - i, CROSS_COLOR, CROSS_ALPHA);
// 		i++;
// 	}
// 	// 下
// 	i = 0;
// 	while (i < LINE_LEN)
// 	{
// 		put_px_alpha(&game->mlx.img, cx, cy + GAP + i, CROSS_COLOR, CROSS_ALPHA);
// 		i++;
// 	}
// 	// 左
// 	i = 0;
// 	while (i < LINE_LEN)
// 	{
// 		put_px_alpha(&game->mlx.img, cx - GAP - i, cy, CROSS_COLOR, CROSS_ALPHA);
// 		i++;
// 	}
// 	// 右
// 	i = 0;
// 	while (i < LINE_LEN)
// 	{
// 		put_px_alpha(&game->mlx.img, cx + GAP + i, cy, CROSS_COLOR, CROSS_ALPHA);
// 		i++;
// 	}
// }

void draw_crosshair(t_game *game, int size, int line_len, int gap, int color, int alpha)
{
    int cx = game->win_width / 2;
    int cy = game->win_height / 2;
    int i, dx, dy;

    // 中心小圆
    for (dy = -size; dy <= size; dy++)
    {
        for (dx = -size; dx <= size; dx++)
        {
            if (dx*dx + dy*dy <= size*size)
                put_px_alpha(&game->mlx.img, cx + dx, cy + dy, color, alpha);
        }
    }

    // 上
    for (i = 0; i < line_len; i++)
        put_px_alpha(&game->mlx.img, cx, cy - gap - i, color, alpha);
    // 下
    for (i = 0; i < line_len; i++)
        put_px_alpha(&game->mlx.img, cx, cy + gap + i, color, alpha);
    // 左
    for (i = 0; i < line_len; i++)
        put_px_alpha(&game->mlx.img, cx - gap - i, cy, color, alpha);
    // 右
    for (i = 0; i < line_len; i++)
        put_px_alpha(&game->mlx.img, cx + gap + i, cy, color, alpha);
}

// void draw_floor_and_ceiling(t_game *game)
// {
//     int x, y;
//     t_img *floor = &game->textures.floor_img;
//     t_img *ceiling = &game->textures.ceiling_img;
//     int color;
//     int tx, ty; // 纹理坐标

//     for (y = 0; y < game->win_height / 2; y++) // 上半屏天空
//     {
//         for (x = 0; x < game->win_width; x++)
//         {
//             // 计算纹理坐标（简单平铺）
//             tx = x % ceiling->width;
//             ty = y % ceiling->height;
//             color = *(int *)(ceiling->data + ty * ceiling->size_line + tx * (ceiling->bpp / 8));
//             put_px(&game->mlx.img, x, y, color);
//         }
//     }

//     for (y = game->win_height / 2; y < game->win_height; y++) // 下半屏地板
//     {
//         for (x = 0; x < game->win_width; x++)
//         {
//             // 计算纹理坐标（简单平铺）
//             tx = x % floor->width;
//             ty = (y - game->win_height / 2) % floor->height;
//             color = *(int *)(floor->data + ty * floor->size_line + tx * (floor->bpp / 8));
//             put_px(&game->mlx.img, x, y, color);
//         }
//     }
// }

