/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:32:23 by jdu               #+#    #+#             */
/*   Updated: 2025/08/28 00:45:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "Libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include "./mlx_linux/mlx.h"
# include <stdio.h>
# include <string.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

/*ORIENTATION*/
# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4
# define NOT_ONBOX 0

/*KEY*/
# define ESC 65307
# define D 100
# define A 97
# define W 119
# define S 115
# define LEFT 65361
# define LEFT_INT 128
# define RIGHT 65363
# define RIGHT_INT 129

/*TEXTURE*/
# define TEXTURE_SIZE 256

/*EVEN*/
# define EVENT_KEY_PRESS    2
# define EVENT_KEY_RELEASE  3
# define EVENT_EXIT         17

# define MOVE_SPEED 0.005
# define ROTATE_SPEED 0.003

/*MINIMAP*/
# define MM_WALL    0x30303A
# define MM_FLOOR   0x70707A
# define MM_PLAYER  0xFF4040
# define MM_BORDER  0x202024
# define MM_ARROW   0xFFAA00

// # define MM_WALL    0xD2691E
// # define MM_FLOOR   0xFFCC99
// # define MM_PLAYER  0xFF4040
// # define MM_BORDER  0x993300
// # define MM_ARROW   0xFFAA00

# define PARSE_GOT_ALL(p) \
	((p)->got_no && (p)->got_so && (p)->got_we && \
	 (p)->got_ea && (p)->got_f  && (p)->got_c)

# define MOUSE_SENSITIVITY 0.00015
# define M_PI 3.14159265358979323846

/*ERROR_INFO*/
# define ERR_MLX "Error: Failed to initialize mlx\n"
# define ERR_TEX "Error: Failed to load textures\n"
# define ERR_KEY "Error: Failed to initialize keys\n"
# define ERR_PLAYER "Error: Failed to initialize player\n"
# define ERR_TEX_PATH "Error: Failed to allocate texture paths\n"

typedef struct s_img
{
	void		*img_ptr;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}	t_img;

typedef struct s_player
{
	double 		x;
	double 		y;
	double 		dir_x;
	double 		dir_y;
	double 		plane_x;
    double 		plane_y;
    double 		plane_len;
}              t_player;

typedef struct s_texture
{
	t_img		no;
	t_img		so;
	t_img		we;
	t_img		ea;
	char 		*no_path;
	char 		*so_path;
	char 		*we_path;
	char 		*ea_path;

	int			floor_color;
	int			ceiling_color;
	int 		floor_r;
	int 		floor_g;
	int 		floor_b;
	int     	ceiling_r;
    int     	ceiling_g;
    int     	ceiling_b;

	// t_img	floor_img;
    // t_img	ceiling_img;
    // char *floor_path;
    // char *ceiling_path;
}	t_texture;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
	int			esc;
}	t_keys;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img   	img;
}	t_mlx;

typedef struct s_game 
{
	t_mlx		mlx;
	t_player	player;
	t_keys		keys;
	t_texture	textures;
	char		**map;
	int			map_width;
	int			map_height;
	int			win_width;
	int			win_height;
}	t_game;

typedef struct s_parse
{
	char		**raw_lines;
	int			raw_count;
	int			map_started;
	int			fd;
	int			got_no;
	int			got_so;
	int			got_we;
	int			got_ea;
	int			got_f;
	int			got_c;
	const char	*filepath;
}	t_parse;

typedef struct s_ray_data
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
}	t_ray_data;

typedef struct s_draw_data
{
	int	line_height;
	int	draw_start;
	int	draw_end;
}	t_draw_data;

typedef struct s_wall_draw_params
{
	t_img	*tex;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		x;
	int		y;
	int		draw_end;
	int		side;
}	t_wall_draw_params;

typedef struct s_crosshair_params
{
	int	size;
	int	line_len;
	int	gap;
	int	color;
	int	alpha;
}	t_crosshair_params;

// typedef struct s_line
// {
// 	int	x0;
// 	int	y0;
// 	int x1;
// 	int y1;
// 	double 	dx;
// 	double 	dy;
// 	double 	sx;
// 	double	sy;
// 	int	steps;
// 	int color;
// }				t_line;

/*PARSER*/
int		is_map_line(const char *line);
int		get_map_width(char **map);
int		get_map_height(char **map);
int		normalize_map(t_game *game, char **raw_lines, int line_count);
int		init_map(t_game *game, const char *filepath);
void	free_map(char **map);
void	free_raw_lines(char **lines, int count);
int 	append_line(char ***arr, int *count, char *line);
void	init_parser(t_parse *p);
char	*trim_whitespace(char *str);
int		is_empty_line(const char *line);
int		is_texture(const char *line);
int		is_color(const char *line);
int		error_msg(const char *msg);


/*INIT && FREE*/
// int		init_game(t_game *game);
int		init_game(t_game *game, const char *map_path);
void	free_game(t_game *game);
int		exit_game(t_game *game, int exit_code);
int		init_img(void *mlx, t_img *img, int width, int height);
void	free_img(void *mlx_ptr, t_img *img);
int		check_and_init_player(t_game *game);
int		init_keys(t_keys *keys);
int		init_mlx(t_mlx *mlx, int width, int height);
void	free_mlx(t_mlx *mlx);
int		init_texture_img(void *mlx_ptr, t_img *img, const char *path);
int    	init_texture_defaults(t_texture *tex);
int		init_textures(t_texture *tex, void *mlx_ptr);
void	free_textures(t_texture *tex, void *mlx_ptr);

/*SETUP*/
void	rotate_player(t_player *p, double angle);
void	update_player(t_game *game);
void	clear_image(t_img *img, int color);
// int		set_up_game(t_game *game);
void set_up_game(t_game *game);
int		render_game(t_game *game);

/*KEY*/
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		exit_button(t_game *game);

/*MOUSE*/
int		mouse_move(int x, int y, t_game *game);

/*MINIMAP*/
void	put_px(t_img *img, int x, int y, int color);
void	draw_rect(t_img *img, int x, int y, int w, int h, int color);
void	draw_line(t_img *img, int x0, int y0, int x1, int y1, int color);
int		minimap_tile_size(t_game *g);
void	draw_border(t_img *img, int x, int y, int w, int h, int color);
void	draw_minimap(t_game *game);

/*RAYCASTING*/
void	draw_crosshair(t_game *game, int size, int line_len, 
			int gap, int color, int alpha);
void	draw_crosshair_center(t_img *img, int cx, int cy, 
				t_crosshair_params *params);
void	draw_crosshair_up(t_img *img, int cx, int cy,
				t_crosshair_params *params);
void	draw_crosshair_down(t_img *img, int cx, int cy,
				t_crosshair_params *params);
void	draw_crosshair_left(t_img *img, int cx, int cy,
				t_crosshair_params *params);
void	draw_crosshair_right(t_img *img, int cx, int cy,
				t_crosshair_params *params);
void	init_crosshair_params(int size, int line_len, int gap,
				int color, int alpha, t_crosshair_params *params);
void	calculate_crosshair_center(t_game *game, int *cx, int *cy);
int		is_valid_coords(t_img *img, int x, int y);
void	extract_color_rgb(int color, int *r, int *g, int *b);
void	extract_bg_rgb(unsigned int bg_color, int *bg_r, 
				int *bg_g, int *bg_b);
void	blend_colors(int r, int g, int b, int bg_r, int bg_g, int bg_b,
				int alpha, int *final_r, int *final_g, int *final_b);
unsigned int	combine_rgb(int final_r, int final_g, int final_b);
void	put_px_alpha(t_img *img, int x, int y, int color, int alpha);

void	cast_rays(t_game *game);
void	render_ray(t_game *game, int x);
void	init_ray_data(t_game *game, double camera_x, t_ray_data *ray);
void	calculate_delta_dist(double ray_dir_x, double ray_dir_y, 
			double *delta_dist_x, double *delta_dist_y);
void	init_step_x(double ray_dir_x, double player_x, 
			int map_x, t_ray_data *ray);
void	init_step_y(double ray_dir_y, double player_y, 
			int map_y, t_ray_data *ray);
void	perform_dda(t_game *game, t_ray_data *ray);
void	dda_step(t_ray_data *ray);
double	calculate_perp_wall_dist(double ray_dir_x, double ray_dir_y,
			t_game *game, t_ray_data *ray);
void	calculate_draw_params(t_game *game, double perp_wall_dist,
			t_draw_data *draw);
t_img	*select_texture(t_game *game, double ray_dir_x, 
			double ray_dir_y, int side);
double	calculate_wall_x(double ray_dir_x, double ray_dir_y,
			t_game *game, t_ray_data *ray, double perp_wall_dist);
int		calculate_tex_x(double wall_x, t_img *tex, double ray_dir_x,
			double ray_dir_y, int side);
void	setup_wall_drawing(t_game *game, t_ray_data *ray, t_draw_data *draw,
			t_wall_draw_params *params, int x, double perp_wall_dist);
void	draw_ceiling(t_game *game, int x, int draw_start);
void	draw_wall(t_game *game, t_wall_draw_params *params);
void	draw_floor(t_game *game, int x, int y);
int		apply_side_shading(int color, int side);

/*MAIN*/
// int		main(int argc, char **argv);

#endif
