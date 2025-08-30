/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selfie_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:11:09 by jdu               #+#    #+#             */
/*   Updated: 2025/08/30 15:05:48 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// 1. 初始化自拍杆系统
void	init_selfie_camera(t_game *game)
{
	game->selfie_cam.x_pos = (game->win_width / 2) - 100;
	game->selfie_cam.y_pos = game->win_height - 240;
	game->selfie_cam.visible = 1;
}

// 2. 加载自拍杆纹理
int	load_selfie_texture(t_game *game)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (0);
	img->img_ptr = mlx_xpm_file_to_image(game->mlx.mlx_ptr, \
			"textures/selfie/selfie.xpm", &img->width, &img->height);
	if (!img->img_ptr)
	{
		free(img);
		return (0);
	}
	img->data = mlx_get_data_addr(img->img_ptr, \
			&img->bpp, &img->size_line, &img->endian);
	game->selfie_cam.selfie_texture = img;
	return (1);
}
