/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:34:31 by jdu               #+#    #+#             */
/*   Updated: 2025/08/26 16:34:32 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// DDA算法执行一步
void	dda_step(t_ray_data *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

// DDA算法寻找墙壁
void	perform_dda(t_game *game, t_ray_data *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		dda_step(ray);
		if (game->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}
