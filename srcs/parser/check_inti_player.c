#include "cub3d.h"

int	check_and_init_player(t_game *game)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
				game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				count++;
				game->player.x = j + 0.5;
				game->player.y = i + 0.5;
				if (game->map[i][j] == 'N')
				{
					game->player.dir_x = 0;
					game->player.dir_y = -1;
				}
				else if (game->map[i][j] == 'S')
				{
					game->player.dir_x = 0;
					game->player.dir_y = 1;
				}
				else if (game->map[i][j] == 'E')
				{
					game->player.dir_x = 1;
					game->player.dir_y = 0;
				}
				else if (game->map[i][j] == 'W')
				{
					game->player.dir_x = -1;
					game->player.dir_y = 0;
				}
				game->player.plane_len = tan(60.0 * M_PI / 180.0 / 2);
				game->player.plane_x = -game->player.dir_y * game->player.plane_len;
				game->player.plane_y = game->player.dir_x * game->player.plane_len;
				game->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (++count > 1)
    	return (0);
	return (count == 1);
}

// int	init_player(t_player *player, char **map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (map[i][j])
// 		{
// 			if (map[i][j] == 'N' || map[i][j] == 'S' ||
// 				map[i][j] == 'E' || map[i][j] == 'W')
// 			{
// 				player->x = j + 0.5;
// 				player->y = i + 0.5;
// 				if (map[i][j] == 'N')
// 				{
// 					player->dir_x = 0;
// 					player->dir_y = -1;
// 				}
// 				else if (map[i][j] == 'S')
// 				{
// 					player->dir_x = 0;
// 					player->dir_y = 1;
// 				}
// 				else if (map[i][j] == 'E')
// 				{
// 					player->dir_x = 1;
// 					player->dir_y = 0;
// 				}
// 				else if (map[i][j] == 'W')
// 				{
// 					player->dir_x = -1;
// 					player->dir_y = 0;
// 				}
// 				player->plane_len = tan(60.0  * M_PI / 180.0 / 2);
//                 player->plane_x = -player->dir_y * player->plane_len;
//                 player->plane_y = player->dir_x * player->plane_len;
// 				map[i][j] = '0';
// 				return (1);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }
