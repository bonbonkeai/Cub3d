#include "cub3d.h"

int	set_up_game(t_game *game)
{
	mlx_hook(game->mlx.win_ptr, X_EVENT_KEY_PRESS, 0, key_press, game);
    mlx_hook(game->mlx.win_ptr, X_EVENT_KEY_RELEASE, 0, key_release, game);
    mlx_hook(game->mlx.win_ptr, X_EVENT_EXIT, 0, exit_button, game);
	mlx_loop_hook(game->mlx.mlx_ptr, render_game, game);
	render_game(game);
	return (1);
}