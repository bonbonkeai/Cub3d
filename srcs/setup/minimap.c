#include "../../cub3d.h"

void	put_px(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->data)
		return;
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return;
	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(int *)dst = color;
}

void	draw_rect(t_img *img, int x, int y, int w, int h, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			put_px(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
	int	steps;
	int	i;
	double dx;
	double dy;
	double sx;
	double sy;
	double cx;
	double cy;

	dx = (double)(x1 - x0);
	dy = (double)(y1 - y0);
	if (fabs(dx) > fabs(dy))
		steps = (int)fabs(dx);
	else
		steps = (int)fabs(dy);
	if (steps <= 0)
	{
		put_px(img, x0, y0, color);
		return ;
	}
	sx = dx / (double)steps;
	sy = dy / (double)steps;
	cx = (double)x0;
	cy = (double)y0;
	i = 0;
	while (i <= steps)
	{
		put_px(img, (int)cx, (int)cy, color);
		cx += sx;
		cy += sy;
		i++;
	}
}

int	minimap_tile_size(t_game *g)
{
	int	max_w;
	int	max_h;
	int	tw;
	int	th;
	int	tile;

	max_w = g->win_width / 3;
	max_h = g->win_height / 3;
	if (g->map_width <= 0 || g->map_height <= 0)
		return (4);
	tw = max_w / g->map_width;
	th = max_h / g->map_height;
	tile = tw;
	if (th < tile)
		tile = th;
	if (tile < 2)
		tile = 2;
	return (tile);
}

void	draw_border(t_img *img, int x, int y, int w, int h, int color)
{
	int	i;

	i = 0;
	while (i < w)
	{
		put_px(img, x + i, y, color);
		put_px(img, x + i, y + h - 1, color);
		i++;
	}
	i = 0;
	while (i < h)
	{
		put_px(img, x, y + i, color);
		put_px(img, x + w - 1, y + i, color);
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int		tile;
	int		offx;
	int		offy;
	int		i;
	int		j;
	int		w;
	int		h;

	if (!game || !game->map || !game->mlx.img.data)
		return ;
	tile = minimap_tile_size(game);
	offx = 8;
	offy = 8;
	w = game->map_width * tile;
	h = game->map_height * tile;
	draw_rect(&game->mlx.img, offx - 1, offy - 1, w + 2, h + 2, 0x0F0F12);
	draw_border(&game->mlx.img, offx - 1, offy - 1, w + 2, h + 2, MM_BORDER);
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == '1')
				draw_rect(&game->mlx.img, offx + j * tile, offy + i * tile,
					tile, tile, MM_WALL);
			else if (game->map[i][j] != '\0')
				draw_rect(&game->mlx.img, offx + j * tile, offy + i * tile,
					tile, tile, MM_FLOOR);
			j++;
		}
		i++;
	}
	{
		int px = offx + (int)(game->player.x * (double)tile);
		int py = offy + (int)(game->player.y * (double)tile);
		int ps;
		if (tile >= 6)
			ps = 4;
		else
			ps = 2;
		draw_rect(&game->mlx.img, px - ps / 2, py - ps / 2, ps, ps, MM_PLAYER);
		{
			int len = tile * 2;
			int lx = px + (int)(game->player.dir_x * (double)len);
			int ly = py + (int)(game->player.dir_y * (double)len);
			draw_line(&game->mlx.img, px, py, lx, ly, MM_PLAYER);
		}
	}
}

