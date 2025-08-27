
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

// 计算两个坐标的差值
static void	calculate_delta(int x0, int y0, int x1, int y1,
				double *dx, double *dy)
{
	*dx = (double)(x1 - x0);
	*dy = (double)(y1 - y0);
}
// static void calculate_delta(t_line line)
// {
// 	*line.dx = (double)(line.x1 - line.x0);
// 	*line.dy = (double)(line.y1 - line.y0);
// }

// 计算绘制步数
static int	calculate_steps(double dx, double dy)
{
	if (fabs(dx) > fabs(dy))
		return ((int)fabs(dx));
	else
		return ((int)fabs(dy));
}

// 计算每步的增量
static void	calculate_increments(double dx, double dy, int steps,
				double *sx, double *sy)
{
	*sx = dx / (double)steps;
	*sy = dy / (double)steps;
}
// static void	calculate_increments(t_line line)
// {
// 	line.*sx = line.dx / (double)line.steps;
// 	line.*sy = line.dy / (double)line.steps;
// }

// 绘制直线的像素点
static void	draw_line_pixels(t_img *img, int x0, int y0,
				double sx, double sy, int steps, int color)
{
	double	cx;
	double	cy;
	int		i;

	cx = (double)x0;
	cy = (double)y0;
	i = 0;
	while (i <= steps)
	{
		put_px(img, (int)cx, (int)cy, color);
		cx += sx;
		cy += sy;
		i++;
	}
}

// static void	draw_line_pixels(t_img *img, t_line line)
// {
// 	double	cx;
// 	double	cy;
// 	int		i;

// 	cx = (double)line.x0;
// 	cy = (double)line.y0;
// 	i = 0;
// 	while (i <= line.steps)
// 	{
// 		put_px(img, (int)cx, (int)cy, line.color);
// 		cx += line.sx;
// 		cy += line.sy;
// 		i++;
// 	}
// }

// 绘制直线主函数
void	draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
	double	dx;
	double	dy;
	double	sx;
	double	sy;
	int		steps;

	calculate_delta(x0, y0, x1, y1, &dx, &dy);
	steps = calculate_steps(dx, dy);
	if (steps <= 0)
	{
		put_px(img, x0, y0, color);
		return ;
	}
	calculate_increments(dx, dy, steps, &sx, &sy);
	draw_line_pixels(img, x0, y0, sx, sy, steps, color);
}

// void	draw_line(t_img *img, t_line line)
// {
// 	double	dx;
// 	double	dy;
// 	double	sx;
// 	double	sy;
// 	int		steps;

// 	calculate_delta(line);
// 	steps = calculate_steps(dx, dy);
// 	if (steps <= 0)
// 	{
// 		put_px(img, x0, y0, color);
// 		return ;
// 	}
// 	calculate_increments(line);
// 	draw_line_pixels(img, line);
// }