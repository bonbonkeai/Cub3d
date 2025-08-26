#include "../../cub3d.h"

// int	mouse_move(int x, int y, t_game *game)
// {
// 	int	center_x;
// 	int	center_y;
// 	int	delta_x;

// 	(void)y;
// 	center_x = game->win_width / 2;
// 	center_y = game->win_height / 2;
// 	delta_x = x - center_x;
// 	if (delta_x != 0)
// 	{
// 		double rot_speed = delta_x * 0.002;
// 		rotate_player(&game->player, rot_speed);
// 		mlx_mouse_move(game->mlx.mlx_ptr, game->mlx.win_ptr, center_x, center_y);
// 	}
// 	return (0);
// }

int mouse_move(int x, int y, t_game *game)
{
    int center_x;
    int center_y;
    int delta_x;
	double max_rot;
	double rot_speed;
	 
	(void)y;
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
        mlx_mouse_move(game->mlx.mlx_ptr, game->mlx.win_ptr, center_x, center_y);
    }
    return (0);
}
