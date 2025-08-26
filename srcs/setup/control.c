#include "../../cub3d.h"

void	rotate_player(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}


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
    // 左右旋转
	if (game->keys.left)
		rotate_player(p, -ROTATE_SPEED);
	if (game->keys.right)
		rotate_player(p, ROTATE_SPEED);
}

void	clear_image(t_img *img, int color)
{
	int		total_pixels;
	int		*dst;
	int		i;

	if (!img || !img->data)
		return;

	total_pixels = img->width * img->height;
	dst = (int *)img->data;
	i = 0;
	while (i < total_pixels)
	{
		dst[i] = color;
		i++;
	}
}

