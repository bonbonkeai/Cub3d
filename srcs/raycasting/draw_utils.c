
#include "../../cub3d.h"

// 22a. 初始化准星像素参数
void init_crosshair_pixel(t_game *game, t_pixel_params *pixel)
{
    pixel->color = game->crosshair.color;
    pixel->alpha = game->crosshair.alpha;
}

// 22b. 获取屏幕中心坐标
void get_screen_center(t_game *game, int *cx, int *cy)
{
    *cx = game->win_width / 2;
    *cy = game->win_height / 2;
}

// 22. 绘制准星中心
// void draw_crosshair_center(t_game *game)
// {
//     int cx;
//     int cy;
//     int dy;
//     int dx;
//     t_pixel_params pixel;
    
//     get_screen_center(game, &cx, &cy);
//     init_crosshair_pixel(game, &pixel);
//     dy = -game->crosshair.size;
//     while (dy <= game->crosshair.size)
//     {
//         dx = -game->crosshair.size;
//         while (dx <= game->crosshair.size)
//         {
//             if (dx*dx + dy*dy <= game->crosshair.size*game->crosshair.size)
//             {
//                 pixel.x = cx + dx;
//                 pixel.y = cy + dy;
//                 put_px_alpha(&game->mlx.img, pixel);
//             }
//             dx++;
//         }
//         dy++;
//     }
// }

static void draw_crosshair_row(t_game *game, int cx, int cy, int dy)
{
    int dx;
    t_pixel_params pixel;

    init_crosshair_pixel(game, &pixel);
    dx = -game->crosshair.size;
    while (dx <= game->crosshair.size)
    {
        if (dx * dx + dy * dy <= game->crosshair.size * game->crosshair.size)
        {
            pixel.x = cx + dx;
            pixel.y = cy + dy;
            put_px_alpha(&game->mlx.img, pixel);
        }
        dx++;
    }
}

void draw_crosshair_center(t_game *game)
{
    int cx;
    int cy;
    int dy;

    get_screen_center(game, &cx, &cy);
    dy = -game->crosshair.size;
    while (dy <= game->crosshair.size)
    {
        draw_crosshair_row(game, cx, cy, dy);
        dy++;
    }
}
