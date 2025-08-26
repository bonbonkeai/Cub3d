/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_px_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:35:03 by jdu               #+#    #+#             */
/*   Updated: 2025/08/26 16:35:05 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// 检查坐标是否在图像范围内
int	is_valid_coords(t_img *img, int x, int y)
{
	if (!img || !img->data)
		return (0);
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0);
	return (1);
}

// 提取颜色的RGB分量
void	extract_color_rgb(int color, int *r, int *g, int *b)
{
	*r = (color >> 16) & 0xFF;
	*g = (color >> 8) & 0xFF;
	*b = color & 0xFF;
}

// 提取背景色的RGB分量
void	extract_bg_rgb(unsigned int bg_color, int *bg_r, 
					int *bg_g, int *bg_b)
{
	*bg_r = (bg_color >> 0) & 0xFF;
	*bg_g = (bg_color >> 8) & 0xFF;
	*bg_b = (bg_color >> 16) & 0xFF;
}

// 执行alpha混合计算
void	blend_colors(int r, int g, int b, int bg_r, int bg_g, int bg_b,
					int alpha, int *final_r, int *final_g, int *final_b)
{
	*final_r = (r * alpha + bg_r * (255 - alpha)) / 255;
	*final_g = (g * alpha + bg_g * (255 - alpha)) / 255;
	*final_b = (b * alpha + bg_b * (255 - alpha)) / 255;
}

// 组合RGB为最终颜色
unsigned int	combine_rgb(int final_r, int final_g, int final_b)
{
	return ((final_b << 16) | (final_g << 8) | final_r);
}
