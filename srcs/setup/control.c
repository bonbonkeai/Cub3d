#include "cub3d.h"

void	update_player(t_game *game)
{
	t_player *p;
    
    p = &game->player;
    //向前
	if (game->keys.w)
	{
		if (game->map[(int)(p->y)][(int)(p->x + p->dir_x * MOVE_SPEED)] != '1')
			p->x += p->dir_x * MOVE_SPEED;
		if (game->map[(int)(p->y + p->dir_y * MOVE_SPEED)][(int)(p->x)] != '1')
			p->y += p->dir_y * MOVE_SPEED;
	}
    //向后
	if (game->keys.s)
	{
		if (game->map[(int)(p->y)][(int)(p->x - p->dir_x * MOVE_SPEED)] != '1')
			p->x -= p->dir_x * MOVE_SPEED;
		if (game->map[(int)(p->y - p->dir_y * MOVE_SPEED)][(int)(p->x)] != '1')
			p->y -= p->dir_y * MOVE_SPEED;
	}
    //向左平移
	if (game->keys.a)
	{
		if (game->map[(int)(p->y)][(int)(p->x - p->plane_x * MOVE_SPEED)] != '1')
			p->x -= p->plane_x * MOVE_SPEED;
		if (game->map[(int)(p->y - p->plane_y * MOVE_SPEED)][(int)(p->x)] != '1')
			p->y -= p->plane_y * MOVE_SPEED;
	}
    //向右平移
	if (game->keys.d)
	{
		if (game->map[(int)(p->y)][(int)(p->x + p->plane_x * MOVE_SPEED)] != '1')
			p->x += p->plane_x * MOVE_SPEED;
		if (game->map[(int)(p->y + p->plane_y * MOVE_SPEED)][(int)(p->x)] != '1')
			p->y += p->plane_y * MOVE_SPEED;
	}
    //左转
	if (game->keys.left)
	{
		double old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(-ROTATE_SPEED) - p->dir_y * sin(-ROTATE_SPEED);
		p->dir_y = old_dir_x * sin(-ROTATE_SPEED) + p->dir_y * cos(-ROTATE_SPEED);
		double old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(-ROTATE_SPEED) - p->plane_y * sin(-ROTATE_SPEED);
		p->plane_y = old_plane_x * sin(-ROTATE_SPEED) + p->plane_y * cos(-ROTATE_SPEED);
	}
    //右转
	if (game->keys.right)
	{
		double old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(ROTATE_SPEED) - p->dir_y * sin(ROTATE_SPEED);
		p->dir_y = old_dir_x * sin(ROTATE_SPEED) + p->dir_y * cos(ROTATE_SPEED);
		double old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(ROTATE_SPEED) - p->plane_y * sin(ROTATE_SPEED);
		p->plane_y = old_plane_x * sin(ROTATE_SPEED) + p->plane_y * cos(ROTATE_SPEED);
	}
}


int	render_game(t_game *game)
{
	update_player(game);
	mlx_clear_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	
    //用玩家视角投射光线生成视图（raycasting）
    // cast_rays(game);
	// draw_walls(game);

	// minimap：
	// draw_minimap(game);
	// draw_crosshair(game);

	return (0);
}
