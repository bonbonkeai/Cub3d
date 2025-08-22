#include "../../cub3d.h"

int	init_mlx(t_mlx *mlx, int width, int height)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, width, height, "cub3D");
	if (!mlx->win_ptr)
		return (0);
	if (!init_img(mlx->mlx_ptr, &mlx->img, width, height))
		return (0);
	return (1);
}

void	free_mlx(t_mlx *mlx)
{
	if (mlx)
	{
		free_img(mlx->mlx_ptr, &mlx->img);
		if (mlx->win_ptr)
		{
			mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
			mlx->win_ptr = NULL;
		}
	}
}
