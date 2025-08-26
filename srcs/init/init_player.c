#include "../../cub3d.h"

int	check_and_init_player(t_game *game)
{
	int		i;
	int		j;
	int		count;
	int		fi;
	int		fj;
	char	fc;

	count = 0;
	fi = -1;
	fj = -1;
	fc = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				if (count == 0)
				{
					fi = i;
					fj = j;
					fc = game->map[i][j];
				}
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		return (ft_fprintf(2, "Error: Found %d player positions, expected 1\n", count), 0);
	game->player.x = fj + 0.5;
	game->player.y = fi + 0.5;
	if (fc == 'N')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
	}
	else if (fc == 'S')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
	}
	else if (fc == 'E')
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
	}
	else if (fc == 'W')
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
	}
	// game->player.plane_len = tan((60.0 * M_PI / 180.0) * 0.5);
	game->player.plane_len = tan((50.0 * M_PI / 180.0) * 0.5);
	game->player.plane_x = -game->player.dir_y * game->player.plane_len;
	game->player.plane_y = game->player.dir_x * game->player.plane_len;
	game->map[fi][fj] = '0';
	ft_printf("Player initialized successfully at: (%.1f, %.1f), facing: %c\n", 
           game->player.x, game->player.y, fc);
	return (1);
}
