#include "cub3d.h"

// int	init_game(t_game *game, char **map, int width, int height)
// {
// 	game->map = map;
// 	game->map_width = width;
// 	game->map_height = height;
// 	game->win_width = WIN_WIDTH;
// 	game->win_height = WIN_HEIGHT;
// 	if (!init_mlx(&game->mlx, game->win_width, game->win_height))
// 	    return (0);
// 	if (!init_player(&game->player, game->map))
// 		return (0);
// 	if (!init_textures(&game->textures, game->mlx.mlx_ptr))
// 		return (0);
// 	if (!init_keys(&game->keys))
// 		return (0);
// 	if (!init_rays(&game->rays, game->win_width))
// 		return (0);
// 	return (1);
// }

int	init_game(t_game *game, char **map, int map_width, int map_height)
{
	game->map = map;
	game->map_width = map_width;
	game->map_height = map_height;
	game->win_width = WIN_WIDTH;
	game->win_height = WIN_HEIGHT;
    game->shadow_factor = 0.7;
	if (!init_mlx(&game->mlx, game->win_width, game->win_height))
	{
		ft_fprintf(2, "Error: Failed to initialize mlx\n");
		exit_game(game, 1);
	}
	if (!init_player(&game->player, game->map))
	{
		ft_fprintf(2, "Error: Failed to initialize player position\n");
		exit_game(game, 1);
	}
	if (!init_textures(&game->textures, game->mlx.mlx_ptr))
	{
		ft_fprintf(2, "Error: Failed to load textures\n");
		exit_game(game, 1);
	}
	if (!init_keys(&game->keys))
	{
		ft_fprintf(2, "Error: Failed to initialize keys\n");
		exit_game(game, 1);
	}
	if (!init_rays(&game->rays, game->win_width))
	{
		ft_fprintf(2, "Error: Failed to initialize rays\n");
		exit_game(game, 1);
	}
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