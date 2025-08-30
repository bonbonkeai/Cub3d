/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:33:52 by jdu               #+#    #+#             */
/*   Updated: 2025/08/30 14:16:09 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	init_texture_data(t_texture *tex)
{
	tex->no.img_ptr = NULL;
	tex->so.img_ptr = NULL;
	tex->we.img_ptr = NULL;
	tex->ea.img_ptr = NULL;
	tex->no.data = NULL;
	tex->so.data = NULL;
	tex->we.data = NULL;
	tex->ea.data = NULL;
	tex->floor_color = 0x6B8E23;
	tex->ceiling_color = 0x87CEEB;
	tex->floor_r = 64;
	tex->floor_g = 64;
	tex->floor_b = 64;
	tex->ceiling_r = 135;
	tex->ceiling_g = 206;
	tex->ceiling_b = 235;
}

int	init_texture_defaults(t_texture *tex)
{
	init_texture_data(tex);
	tex->no_path = ft_strdup("textures/mur/north.xpm");
	tex->so_path = ft_strdup("textures/mur/south.xpm");
	tex->we_path = ft_strdup("textures/mur/west.xpm");
	tex->ea_path = ft_strdup("textures/mur/east.xpm");
	if (!tex->no_path || !tex->so_path || \
		!tex->we_path || !tex->ea_path)
		return (ft_fprintf(2, ERR_TEX_PATH), 0);
	return (1);
}

int	init_texture_img(void *mlx_ptr, t_img *img, const char *path)
{
	if (!mlx_ptr || !img || !path || *path == '\0')
		return (0);
	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, (char *)path, \
						&img->width, &img->height);
	if (!img->img_ptr)
		return (0);
	img->data = mlx_get_data_addr(img->img_ptr, \
				&img->bpp, &img->size_line, &img->endian);
	if (!img->data)
	{
		mlx_destroy_image(mlx_ptr, img->img_ptr);
		img->img_ptr = NULL;
		return (0);
	}
	return (1);
}

static int	check_all_paths_ready(t_texture *t)
{
	if (!t->no_path || !t->so_path)
		return (0);
	if (!t->we_path || !t->ea_path)
		return (0);
	return (1);
}

int	init_textures(t_texture *tex, void *mlx_ptr)
{
	if (!check_all_paths_ready(tex))
		return (0);
	if (!init_texture_img(mlx_ptr, &tex->no, tex->no_path) || \
		!init_texture_img(mlx_ptr, &tex->so, tex->so_path) || \
		!init_texture_img(mlx_ptr, &tex->we, tex->we_path) || \
		!init_texture_img(mlx_ptr, &tex->ea, tex->ea_path))
	{
		free_textures(tex, mlx_ptr);
		return (0);
	}
	return (1);
}
