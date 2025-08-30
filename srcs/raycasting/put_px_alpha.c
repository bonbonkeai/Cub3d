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

// 21d. 执行颜色混合
void perform_color_blending(int *fg_colors, int *bg_colors, int alpha)
{
    fg_colors[0] = blend_channel(fg_colors[0], bg_colors[0], alpha);
    fg_colors[1] = blend_channel(fg_colors[1], bg_colors[1], alpha);
    fg_colors[2] = blend_channel(fg_colors[2], bg_colors[2], alpha);
}

// 21e. 组合最终颜色
unsigned int combine_final_color(int *colors)
{
    return ((colors[2] << 16) | (colors[1] << 8) | colors[0]);
}

// 21f. 写入像素到目标地址
void write_pixel_to_buffer(char *dst, unsigned int final_color)
{
    *(unsigned int *)dst = final_color;
}

void put_px_alpha(t_img *img, t_pixel_params params)
{
    char *dst;
    unsigned int bg_color;
    unsigned int final_color;
    int fg_colors[3];
    int bg_colors[3];
    
    if (!validate_image_bounds(img, params.x, params.y))
        return ;
    dst = get_pixel_address(img, params.x, params.y);
    bg_color = *(unsigned int *)dst;
    extract_colors(params.color, &fg_colors[0], &fg_colors[1], &fg_colors[2]);
    extract_bg_colors(bg_color, bg_colors);
    perform_color_blending(fg_colors, bg_colors, params.alpha);
    final_color = combine_final_color(fg_colors);
    write_pixel_to_buffer(dst, final_color);
}
