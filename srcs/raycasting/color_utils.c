
#include "../../cub3d.h"

// 19. alpha混合辅助函数
int blend_channel(int fg, int bg, int alpha)
{
    return ((fg * alpha + bg * (255 - alpha)) / 255);
}

// 20. 提取颜色分量
void extract_colors(int color, int *r, int *g, int *b)
{
    *r = (color >> 16) & 0xFF;
    *g = (color >> 8) & 0xFF;
    *b = color & 0xFF;
}

// 21. Alpha混合像素绘制
// 21a. 验证图像和坐标有效性
int validate_image_bounds(t_img *img, int x, int y)
{
    if (!img || !img->data)
        return (0);
    if (x < 0 || y < 0 || x >= img->width || y >= img->height)
        return (0);
    return (1);
}

// 21b. 获取像素地址
char *get_pixel_address(t_img *img, int x, int y)
{
    return (img->data + (y * img->size_line + x * (img->bpp / 8)));
}

// 21c. 提取背景颜色分量
void extract_bg_colors(unsigned int bg_color, int *bg)
{
    bg[0] = (bg_color >> 0) & 0xFF;
    bg[1] = (bg_color >> 8) & 0xFF;
    bg[2] = (bg_color >> 16) & 0xFF;
}
