/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:36:04 by jdu               #+#    #+#             */
/*   Updated: 2025/08/30 15:01:19 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	mouse_move(int x, int y, t_game *game)
{
	int		center_x;
	int		center_y;
	int		delta_x;
	double	max_rot;
	double	rot_speed;

	(void)y;
	if (!game->keys.mouse_control)
		return (0);
	center_x = game->win_width / 2;
	center_y = game->win_height / 2;
	delta_x = x - center_x;
	max_rot = 0.05;
	if (delta_x != 0)
	{
		rot_speed = delta_x * MOUSE_SENSITIVITY;
		if (rot_speed > max_rot)
			rot_speed = max_rot;
		else if (rot_speed < -max_rot)
			rot_speed = -max_rot;
		rotate_player(&game->player, rot_speed);
		mlx_mouse_move(game->mlx.mlx_ptr, game->mlx.win_ptr, \
				center_x, center_y);
	}
	return (0);
}
