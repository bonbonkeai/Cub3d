#include "cub3d.h"

int	init_player(t_player *player, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
			{
				player->x = j + 0.5;
				player->y = i + 0.5;
				if (map[i][j] == 'N')
				{
					player->dir_x = 0;
					player->dir_y = -1;
				}
				else if (map[i][j] == 'S')
				{
					player->dir_x = 0;
					player->dir_y = 1;
				}
				else if (map[i][j] == 'E')
				{
					player->dir_x = 1;
					player->dir_y = 0;
				}
				else if (map[i][j] == 'W')
				{
					player->dir_x = -1;
					player->dir_y = 0;
				}
				player->view = 0.66;
				map[i][j] = '0';
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}


