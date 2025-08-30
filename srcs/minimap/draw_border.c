#include "../../cub3d.h"


// void	draw_border(t_img *img, int x, int y, int w, int h, int color)
// {
// 	int	i;

// 	i = 0;
// 	while (i < w)
// 	{
// 		put_px(img, x + i, y, color);
// 		put_px(img, x + i, y + h - 1, color);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < h)
// 	{
// 		put_px(img, x, y + i, color);
// 		put_px(img, x + w - 1, y + i, color);
// 		i++;
// 	}
// }

// 4. 绘制水平边框线
void draw_horizontal_border(t_img *img, t_row_params params)
{
    int i;
    
    if (!img)
        return;
    i = 0;
    while (i < params.width)
    {
        put_px(img, params.x + i, params.y, params.color);
        i++;
    }
}

// 5. 绘制垂直边框线
void draw_vertical_border(t_img *img, t_row_params params)
{
    int i;
    
    if (!img)
        return;
    i = 0;
    while (i < params.width)
    {
        put_px(img, params.x, params.y + i, params.color);
        i++;
    }
}

// 6. 绘制完整边框
void draw_border(t_img *img, t_rect_params params)
{
    t_row_params h_border;
    t_row_params v_border;
    
    if (!img || !validate_rect_params(&params))
        return ;
    // 上边框
    h_border.x = params.x;
    h_border.y = params.y;
    h_border.width = params.width;
    h_border.color = params.color;
    draw_horizontal_border(img, h_border);
    // 下边框
    h_border.y = params.y + params.height - 1;
    draw_horizontal_border(img, h_border);
    // 左边框
    v_border.x = params.x;
    v_border.y = params.y;
    v_border.width = params.height;
    v_border.color = params.color;
    draw_vertical_border(img, v_border);
    // 右边框
    v_border.x = params.x + params.width - 1;
    draw_vertical_border(img, v_border);
}
