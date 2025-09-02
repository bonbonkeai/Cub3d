/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:33:39 by jdu               #+#    #+#             */
/*   Updated: 2025/08/26 16:33:41 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// int	check_and_init_player(t_game *game)
// {
// 	int		i;
// 	int		j;
// 	int		count;
// 	int		fi;
// 	int		fj;
// 	char	fc;

// 	count = 0;
// 	fi = -1;
// 	fj = -1;
// 	fc = 0;
// 	i = 0;
// 	while (i < game->map_height)
// 	{
// 		j = 0;
// 		while (j < game->map_width)
// 		{
// 			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
// 				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
// 			{
// 				if (count == 0)
// 				{
// 					fi = i;
// 					fj = j;
// 					fc = game->map[i][j];
// 				}
// 				count++;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	if (count != 1)
// 		return (ft_fprintf(2, "Error: Found %d player positions, expected 1\n", count), 0);
// 	game->player.x = fj + 0.5;
// 	game->player.y = fi + 0.5;
// 	if (fc == 'N')
// 	{
// 		game->player.dir_x = 0.0;
// 		game->player.dir_y = -1.0;
// 	}
// 	else if (fc == 'S')
// 	{
// 		game->player.dir_x = 0.0;
// 		game->player.dir_y = 1.0;
// 	}
// 	else if (fc == 'E')
// 	{
// 		game->player.dir_x = 1.0;
// 		game->player.dir_y = 0.0;
// 	}
// 	else if (fc == 'W')
// 	{
// 		game->player.dir_x = -1.0;
// 		game->player.dir_y = 0.0;
// 	}
// 	// game->player.plane_len = tan((60.0 * M_PI / 180.0) * 0.5);
// 	game->player.plane_len = tan((50.0 * M_PI / 180.0) * 0.5);
// 	game->player.plane_x = -game->player.dir_y * game->player.plane_len;
// 	game->player.plane_y = game->player.dir_x * game->player.plane_len;
// 	game->map[fi][fj] = '0';
// 	// ft_printf("Player initialized successfully at: (%.1f, %.1f), facing: %c\n", 
//     //        game->player.x, game->player.y, fc);
// 	return (1);
// }

// 检查字符是否为玩家方向标识
static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

// 查找地图中的玩家位置
static int	find_player_position(t_game *game, int *fi, int *fj, char *fc)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	*fi = -1;
	*fj = -1;
	*fc = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (is_player_char(game->map[i][j]))
			{
				if (count == 0)
				{
					*fi = i;
					*fj = j;
					*fc = game->map[i][j];
				}
				count++;
			}
			j++;
		}
		i++;
	}
	return (count);
}

// 根据方向字符设置玩家朝向
static void	set_player_direction(t_game *game, char direction)
{
	if (direction == 'N')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
	}
	else if (direction == 'S')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
	}
	else if (direction == 'E')
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
	}
	else if (direction == 'W')
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
	}
}

// 初始化玩家数据
static void	init_player_data(t_game *game, int fi, int fj, char fc)
{
	game->player.x = fj + 0.5;
	game->player.y = fi + 0.5;
	set_player_direction(game, fc);
	game->player.plane_len = tan((50.0 * M_PI / 180.0) * 0.5);
	game->player.plane_x = -game->player.dir_y * game->player.plane_len;
	game->player.plane_y = game->player.dir_x * game->player.plane_len;
	game->map[fi][fj] = '0';
}

// 检查并初始化玩家
int	check_and_init_player(t_game *game)
{
	int		count;
	int		fi;
	int		fj;
	char	fc;

	count = find_player_position(game, &fi, &fj, &fc);
	if (count != 1)
		return (ft_fprintf(2, 
			"Error: Found %d player positions, expected 1\n", count), 0);
	init_player_data(game, fi, fj, fc);
	return (1);
}