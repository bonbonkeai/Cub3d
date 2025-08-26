#include "../../cub3d.h"

int	init_game(t_game *game, const char *map_path)
{
	game->win_width = WIN_WIDTH;
	game->win_height = WIN_HEIGHT;
	if (!init_mlx(&game->mlx, game->win_width, game->win_height))
	{
		ft_fprintf(2, "Error: Failed to initialize mlx\n");
		free_game(game);
		return (0);
	}
    if (!init_map(game, map_path))
	{
		ft_fprintf(2, "Error: Failed to load map from file '%s'\n", map_path);
		free_game(game);
		return (0);
	}
	if (!check_and_init_player(game))
	{
		ft_fprintf(2, "Error: Failed to initialize player\n");
        free_game(game);
		return (0);
	}
	if (!init_texture_defaults(&game->textures))
	{
		free_game(game);
		return (0);
	}
	if (!init_textures(&game->textures, game->mlx.mlx_ptr))
	{
		ft_fprintf(2, "Error: Failed to load textures\n");
		free_game(game);
		return (0);
	}
	if (!init_keys(&game->keys))
	{
		ft_fprintf(2, "Error: Failed to initialize keys\n");
		free_game(game);
		return (0);
	}
	if (!init_rays(&game->rays, game->win_width))
	{
		ft_fprintf(2, "Error: Failed to initialize rays\n");
		free_game(game);
		return (0);
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
