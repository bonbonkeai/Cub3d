#include "../../cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == W)
		game->keys.w = 1;
	else if (keycode == A)
		game->keys.a = 1;
	else if (keycode == S)
		game->keys.s = 1;
	else if (keycode == D)
		game->keys.d = 1;
	else if (keycode == LEFT || keycode == LEFT_INT)
		game->keys.left = 1;
	else if (keycode == RIGHT || keycode == RIGHT_INT)
		game->keys.right = 1;
	else if (keycode == ESC)
		exit_game(game, 0);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->keys.w = 0;
	else if (keycode == A)
		game->keys.a = 0;
	else if (keycode == S)
		game->keys.s = 0;
	else if (keycode == D)
		game->keys.d = 0;
	else if (keycode == LEFT || keycode == LEFT_INT)
		game->keys.left = 0;
	else if (keycode == RIGHT || keycode == RIGHT_INT)
		game->keys.right = 0;
	return (0);
}

int	exit_button(t_game *game)
{
	return (exit_game(game, 0));
}
