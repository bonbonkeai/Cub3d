#include "cub3d.h"

// int	init_texture_img(void *mlx_ptr, t_img *img, char *path)
// {
// 	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &img->width, &img->height);
// 	if (!img->img_ptr)
// 		return (0);
// 	img->data = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian);
// 	if (!img->data)
// 		return (0);
// 	return (1);
// }

// void	free_textures(t_texture *tex, void *mlx_ptr)
// {
// 	free_img(mlx_ptr, &tex->no);
// 	free_img(mlx_ptr, &tex->so);
// 	free_img(mlx_ptr, &tex->we);
// 	free_img(mlx_ptr, &tex->ea);
// }

int	init_texture_img(void *mlx_ptr, t_img *img, char *path)
{
	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &img->width, &img->height);
	if (!img->img_ptr)
		return (0);
	img->data = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian);
	if (!img->data)
	{
		mlx_destroy_image(mlx_ptr, img->img_ptr);
		img->img_ptr = NULL;
		return (0);
	}
	return (1);
}

void	free_textures(t_texture *tex, void *mlx_ptr)
{
	free_img(mlx_ptr, &tex->no);
	free_img(mlx_ptr, &tex->so);
	free_img(mlx_ptr, &tex->we);
	free_img(mlx_ptr, &tex->ea);
	free(tex->no_path);
	free(tex->so_path);
	free(tex->we_path);
	free(tex->ea_path);
	tex->no_path = NULL;
	tex->so_path = NULL;
	tex->we_path = NULL;
	tex->ea_path = NULL;
}

int	init_textures(t_texture *tex, void *mlx_ptr)
{
    if (!init_texture_img(mlx_ptr, &tex->no, tex->no_path)
    || !init_texture_img(mlx_ptr, &tex->so, tex->so_path)
    || !init_texture_img(mlx_ptr, &tex->we, tex->we_path)
    || !init_texture_img(mlx_ptr, &tex->ea, tex->ea_path))
    {
        free_textures(tex, mlx_ptr);
        return (0);
    }
	return (1);
}