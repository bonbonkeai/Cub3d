#include "cub3d.h"

int	init_game(t_game *game, const char *map_path)
{
	if (!init_map(game, map_path))
		return (0);
	game->win_width = WIN_WIDTH;
	game->win_height = WIN_HEIGHT;
	if (!init_mlx(&game->mlx, game->win_width, game->win_height))
	    return (0);
	if (!init_player(&game->player, game->map))
		return (0);
	if (!init_textures(&game->textures, game->mlx.mlx_ptr))
		return (0);
	if (!init_keys(&game->keys))
		return (0);
	if (!init_rays(&game->rays, game->win_width))
		return (0);
	return (1);
}

void	free_game(t_game *game)
{
	if (game->map)
		free_map(game->map);
	if (game->rays)
		free_rays(&game->rays);
	free_textures(&game->textures, game->mlx.mlx_ptr);
	free_mlx(&game->mlx);
}

int	exit_game(t_game *game, int exit_code)
{
    free_game(game);
	if (game->mlx.mlx_ptr)
	{
		mlx_destroy_display(game->mlx.mlx_ptr);
		free(game->mlx.mlx_ptr);
		game->mlx.mlx_ptr = NULL;
	}
	exit(exit_code);
}