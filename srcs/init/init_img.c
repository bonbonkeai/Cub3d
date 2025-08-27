/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:32:52 by jdu               #+#    #+#             */
/*   Updated: 2025/08/27 17:54:32 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	init_img(void *mlx, t_img *img, int width, int height)
{
	img->img_ptr = mlx_new_image(mlx, width, height);
	if (!img->img_ptr)
		return (0);
	img->data = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, \
					&img->endian);
	if (!img->data)
		return (0);
	img->width = width;
	img->height = height;
	return (1);
}

void	free_img(void *mlx_ptr, t_img *img)
{
	if (img)
	{
		if (mlx_ptr && img->img_ptr)
			mlx_destroy_image(mlx_ptr, img->img_ptr);
		img->img_ptr = NULL;
		img->data = NULL;
		img->width = 0;
		img->height = 0;
		img->bpp = 0;
		img->size_line = 0;
		img->endian = 0;
	}
}
