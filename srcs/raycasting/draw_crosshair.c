/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_crosshair.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:34:49 by jdu               #+#    #+#             */
/*   Updated: 2025/08/26 16:34:51 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// 绘制准星中心圆形
void	draw_crosshair_center(t_img *img, int cx, int cy, 
						t_crosshair_params *params)
{
	int	dy;
	int	dx;

	dy = -params->size;
	while (dy <= params->size)
	{
		dx = -params->size;
		while (dx <= params->size)
		{
			if (dx * dx + dy * dy <= params->size * params->size)
				put_px_alpha(img, cx + dx, cy + dy, params->color, params->alpha);
			dx++;
		}
		dy++;
	}
}

// 绘制准星上方线条
void	draw_crosshair_up(t_img *img, int cx, int cy,
					t_crosshair_params *params)
{
	int	i;

	i = 0;
	while (i < params->line_len)
	{
		put_px_alpha(img, cx, cy - params->gap - i, params->color, params->alpha);
		i++;
	}
}

// 绘制准星下方线条
void	draw_crosshair_down(t_img *img, int cx, int cy,
					t_crosshair_params *params)
{
	int	i;

	i = 0;
	while (i < params->line_len)
	{
		put_px_alpha(img, cx, cy + params->gap + i, params->color, params->alpha);
		i++;
	}
}

// 绘制准星左侧线条
void	draw_crosshair_left(t_img *img, int cx, int cy,
					t_crosshair_params *params)
{
	int	i;

	i = 0;
	while (i < params->line_len)
	{
		put_px_alpha(img, cx - params->gap - i, cy, params->color, params->alpha);
		i++;
	}
}

// 绘制准星右侧线条
void	draw_crosshair_right(t_img *img, int cx, int cy,
					t_crosshair_params *params)
{
	int	i;

	i = 0;
	while (i < params->line_len)
	{
		put_px_alpha(img, cx + params->gap + i, cy, params->color, params->alpha);
		i++;
	}
}
