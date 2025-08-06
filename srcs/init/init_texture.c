#include "cub3d.h"

int	init_texture_img(void *mlx_ptr, t_img *img, char *path)
{
	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &img->width, &img->height);
	if (!img->img_ptr)
		return (0);
	img->data = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian);
	if (!img->data)
		return (0);
	return (1);
}

void	free_textures(t_texture *tex, void *mlx_ptr)
{
	free_img(mlx_ptr, &tex->no);
	free_img(mlx_ptr, &tex->so);
	free_img(mlx_ptr, &tex->we);
	free_img(mlx_ptr, &tex->ea);
}

int	init_textures(t_texture *tex, void *mlx_ptr)
{
	if (!init_texture_img(mlx_ptr, &tex->no, TEX_NORTH)
		|| !init_texture_img(mlx_ptr, &tex->so, TEX_SOUTH)
		|| !init_texture_img(mlx_ptr, &tex->we, TEX_WEST)
		|| !init_texture_img(mlx_ptr, &tex->ea, TEX_EAST))
	{
		free_textures(tex, mlx_ptr);
		return (0);
	}
	tex->floor_color = 0x333333;
	tex->ceiling_color = 0xAAAAAA;
	return (1);
}