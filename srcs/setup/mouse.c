#include "cub3d.h"

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
	else if (keycode == LEFT)
		game->keys.left = 1;
	else if (keycode == RIGHT)
		game->keys.right = 1;
	else if (keycode == LEFT_INT)
		game->keys.left = 1;
	else if (keycode == RIGHT_INT)
		game->keys.right = 1;
	else if (keycode == ESC)
		game->keys.esc = 1;
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
	else if (keycode == LEFT)
		game->keys.left = 0;
	else if (keycode == RIGHT)
		game->keys.right = 0;
	else if (keycode == LEFT_INT)
		game->keys.left = 0;
	else if (keycode == RIGHT_INT)
		game->keys.right = 0;
	else if (keycode == ESC)
		game->keys.esc = 0;
	return (0);
}