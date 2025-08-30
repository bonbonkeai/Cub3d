/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:18:16 by jdu               #+#    #+#             */
/*   Updated: 2025/08/30 15:18:48 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// void	draw_rect(t_img *img, int x, int y, int w, int h, int color)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < h)
// 	{
// 		j = 0;
// 		while (j < w)
// 		{
// 			put_px(img, x + j, y + i, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// 1. 验证矩形参数有效性
int	validate_rect_params(t_rect_params *params)
{
	if (params->width <= 0 || params->height <= 0)
		return (0);
	return (1);
}

// 2. 绘制矩形的单行
void	draw_rect_row(t_img *img, t_row_params params)
{
	int	j;

	if (!img)
		return ;
	j = 0;
	while (j < params.width)
	{
		put_px(img, params.x + j, params.y, params.color);
		j++;
	}
}

// 3. 绘制完整矩形
void	draw_rect(t_img *img, t_rect_params params)
{
	int				i;
	t_row_params	row;

	if (!img || !validate_rect_params(&params))
		return ;
	row.x = params.x;
	row.width = params.width;
	row.color = params.color;
	i = 0;
	while (i < params.height)
	{
		row.y = params.y + i;
		draw_rect_row(img, row);
		i++;
	}
}
