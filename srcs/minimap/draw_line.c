
#include "../../cub3d.h"

// void	draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
// {
// 	int	steps;
// 	int	i;
// 	double dx;
// 	double dy;
// 	double sx;
// 	double sy;
// 	double cx;
// 	double cy;

// 	dx = (double)(x1 - x0);
// 	dy = (double)(y1 - y0);
// 	if (fabs(dx) > fabs(dy))
// 		steps = (int)fabs(dx);
// 	else
// 		steps = (int)fabs(dy);
// 	if (steps <= 0)
// 	{
// 		put_px(img, x0, y0, color);
// 		return ;
// 	}
// 	sx = dx / (double)steps;
// 	sy = dy / (double)steps;
// 	cx = (double)x0;
// 	cy = (double)y0;
// 	i = 0;
// 	while (i <= steps)
// 	{
// 		put_px(img, (int)cx, (int)cy, color);
// 		cx += sx;
// 		cy += sy;
// 		i++;
// 	}
// }

// 11. 计算直线步数
int calculate_line_steps(int dx, int dy)
{
    if (ft_abs(dx) > ft_abs(dy))
        return ((int)ft_abs(dx));
    return ((int)ft_abs(dy));
}

// 12. 计算直线步长
void calculate_line_increments(t_line_params *params, t_line_step *step)
{
    double dx;
    double dy;
    int steps;
    
    dx = (double)(params->x1 - params->x0);
    dy = (double)(params->y1 - params->y0);
    steps = calculate_line_steps(dx, dy);
    if (steps <= 0)
    {
        step->sx = 0;
        step->sy = 0;
        return ;
    }
    step->sx = dx / (double)steps;
    step->sy = dy / (double)steps;
}

// 13. 绘制直线像素点
void draw_line_pixels(t_img *img, t_line_params *params)
{
    t_line_step step;
    double cx;
    double cy;
    int steps;
    int i;
    
    calculate_line_increments(params, &step);
    steps = calculate_line_steps(params->x1 - params->x0, params->y1 - params->y0);
    if (steps <= 0)
    {
        put_px(img, params->x0, params->y0, params->color);
        return ;
    }
    cx = (double)params->x0;
    cy = (double)params->y0;
    i = 0;
    while (i <= steps)
    {
        put_px(img, (int)cx, (int)cy, params->color);
        cx += step.sx;
        cy += step.sy;
        i++;
    }
}

// 14. 绘制直线主函数
void draw_line(t_img *img, t_line_params params)
{
    if (!img)
        return ;
    draw_line_pixels(img, &params);
}