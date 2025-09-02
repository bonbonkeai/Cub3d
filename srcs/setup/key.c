/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:35:50 by jdu               #+#    #+#             */
/*   Updated: 2025/08/30 14:59:12 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	key_mouse(t_game *game)
{
	game->keys.mouse_control = !game->keys.mouse_control;
	if (game->keys.mouse_control)
	{
		// mlx_mouse_hide(game->mlx.mlx_ptr, game->mlx.win_ptr);
		mlx_mouse_move(game->mlx.mlx_ptr, game->mlx.win_ptr, \
				game->win_width / 2, game->win_height / 2);
	}
	else
		mlx_mouse_show(game->mlx.mlx_ptr, game->mlx.win_ptr);
}

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
	else if (keycode == TAB)
		key_mouse(game);
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
