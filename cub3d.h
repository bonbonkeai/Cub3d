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
# include <sys/stat.h>
# include <stdlib.h>
# include <unistd.h>
# include "./mlx_linux/mlx.h"
# include <stdio.h>
# include <string.h>
# include <time.h>

# define WIN_WIDTH 1000
# define WIN_HEIGHT 800

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
# define TAB 65289

/*TEXTURE*/
# define TEXTURE_SIZE 256

/*EVEN*/
# define EVENT_KEY_PRESS    2
# define EVENT_KEY_RELEASE  3
# define EVENT_EXIT         17

# define MOVE_SPEED 0.006
# define ROTATE_SPEED 0.004

/*MINIMAP*/
// # define MM_WALL    0x30303A
// # define MM_FLOOR   0x70707A
// # define MM_PLAYER  0xFF4040
// # define MM_BORDER  0x202024
// # define MM_ARROW   0xFFAA00

// #define MM_WALL    0xCD853F  // 秘鲁色（浅棕橙）
// #define MM_FLOOR   0x556B2F
// #define MM_PLAYER  0xFF4500  // 橙红色
// #define MM_BORDER  0x000000  // 纯黑边框
// #define MM_ARROW   0xFFFF00  // 纯黄箭头

#define MM_WALL    0xEA955D  // 秘鲁色（浅棕橙）
#define MM_FLOOR   0x7BA72E
#define MM_PLAYER  0xFF4500  // 橙红色
#define MM_BORDER  0x000000  // 纯黑边框
#define MM_ARROW   0xFFFF00  // 纯黄箭头

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
# define ERR_SELFIE "Failed to load selfie stick texture!\n"

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

	t_img   selfie_texture;
	char	*selfie_path;
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

	int			mouse_control;
}	t_keys;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img   	img;
}	t_mlx;

typedef struct s_crosshair
{
	int	size;
	int	line_len;
	int	gap;
	int	color;
	int	alpha;
}	t_crosshair;

typedef struct s_ray
{
    double  ray_dir_x;
    double  ray_dir_y;
    int     map_x;
    int     map_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  side_dist_x;
    double  side_dist_y;
    int     step_x;
    int     step_y;
    int     side;
} t_ray;

typedef struct s_draw
{
    int     line_height;
    int     draw_start;
    int     draw_end;
} t_draw;

typedef struct s_wall_params
{
    t_img   *tex;
    int     tex_x;
    double  step;
    double  tex_pos;
} t_wall_params;

typedef struct s_pixel_params
{
    int x;
    int y;
    int color;
    int alpha;
} t_pixel_params;

typedef struct s_rect_params
{
    int x;
    int y;
    int width;
    int height;
    int color;
} t_rect_params;

typedef struct s_line_params
{
    int x0;
    int y0;
    int x1;
    int y1;
    int color;
} t_line_params;

typedef struct s_tile_calc
{
    int max_w;
    int max_h;
    int tw;
    int th;
} t_tile_calc;

typedef struct s_row_params
{
    int x;
    int y;
    int width;
    int color;
} t_row_params;

typedef struct s_line_step
{
    double sx;
    double sy;
} t_line_step;

typedef struct s_tile_pos
{
    int i;
    int j;
} t_tile_pos;

typedef struct s_minimap
{
    int tile_size;
    int offset_x;
    int offset_y;
    int total_width;
    int total_height;
    int player_size;
} t_minimap;

typedef struct s_selfie_camera
{
    t_img   *selfie_texture;
    int     x_pos;
    int     y_pos;
    int     visible;
} t_selfie_camera;

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
	t_ray           ray;
    t_draw          draw;
    t_wall_params   wall_params;
    t_crosshair     crosshair;
	t_minimap		minimap;
    double                  temp_perp_dist;
    double                  temp_wall_x;
	t_selfie_camera selfie_cam;
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
	t_texture	*textures;
}	t_parse;

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
int		parse_rgb_values(const char *rgb_str, int *r, int *g, int *b);
int		parse_color(char *line, t_parse *parser);
int		parse_texture(char *line, t_parse *parser);


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
void    init_game_structs(t_game *game);
void	init_ray(t_game *game);
void 	init_game_structures(t_game *game);

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
// 矩形绘制
int     validate_rect_params(t_rect_params *params);
void    draw_rect_row(t_img *img, t_row_params params);
void    draw_rect(t_img *img, t_rect_params params);

// 边框绘制  
void    draw_horizontal_border(t_img *img, t_row_params params);
void    draw_vertical_border(t_img *img, t_row_params params);
void    draw_border(t_img *img, t_rect_params params);

// 尺寸计算
void    calculate_max_minimap_size(t_game *game, int *max_w, int *max_h);
void    calculate_tile_dimensions(t_game *game, t_tile_calc *calc);
int     select_minimum_tile_size(int tw, int th);
int     minimap_tile_size(t_game *game);

// 直线绘制
int     calculate_line_steps(int dx, int dy);
void    calculate_line_increments(t_line_params *params, t_line_step *step);
void    draw_line_pixels(t_img *img, t_line_params *params);
void    draw_line(t_img *img, t_line_params params);

// Minimap初始化和绘制
void    init_minimap_params(t_game *game);
void    draw_minimap_background(t_game *game);
int     is_wall_tile(const char tile);
int     is_floor_tile(const char tile);
void    draw_map_tile(t_game *game, t_tile_pos pos);
void    draw_map_tiles(t_game *game);
void    calculate_player_screen_pos(t_game *game, int *px, int *py);
void    draw_player_marker(t_game *game);
void    draw_player_direction(t_game *game);
void    draw_minimap(t_game *game);
void	draw_wall_shadows(t_game *game);
void	draw_tile_shadow(t_game *game, t_tile_pos pos, int shadow_offset);

// /*RAYCASTING*/
//像素绘制函数
void    put_px(t_img *img, int x, int y, int color);
void    put_px_alpha(t_img *img, t_pixel_params params);

//射线投射核心函数
void    init_ray_for_column(t_game *game, int x);
void    calculate_delta_distances(t_game *game);
void    calculate_step_x(t_game *game);
void    calculate_step_y(t_game *game);
void    dda_step(t_game *game);
void    perform_dda(t_game *game);
void    calculate_perp_wall_dist(t_game *game);
void    calculate_draw_range(t_game *game);

//纹理相关函数
void    select_wall_texture(t_game *game);
void    calculate_wall_hit(t_game *game);
void    calculate_tex_x(t_game *game);
void    calculate_texture_step(t_game *game);

//渲染函数
void    draw_ceiling(t_game *game, int x);
void    draw_wall(t_game *game, int x);
void    draw_floor(t_game *game, int x);
void    draw_column(t_game *game, int x);
void    cast_rays(t_game *game);

//阴影和颜色处理
int     apply_side_shading(int color, int side);
int     blend_channel(int fg, int bg, int alpha);
void    extract_colors(int color, int *r, int *g, int *b);

//Alpha混合辅助函数
int             validate_image_bounds(t_img *img, int x, int y);
char            *get_pixel_address(t_img *img, int x, int y);
void            extract_bg_colors(unsigned int bg_color, int *bg);
void            perform_color_blending(int *fg_colors, int *bg_colors, int alpha);
unsigned int    combine_final_color(int *colors);
void            write_pixel_to_buffer(char *dst, unsigned int final_color);

//准星绘制函数
void    init_crosshair_pixel(t_game *game, t_pixel_params *pixel);
void    get_screen_center(t_game *game, int *cx, int *cy);
void    draw_crosshair_center(t_game *game);
void    draw_crosshair_up(t_game *game);
void    draw_crosshair_down(t_game *game);
void    draw_crosshair_left(t_game *game);
void    draw_crosshair_right(t_game *game);
void    draw_crosshair(t_game *game);

//静态自拍杆系统函数声明
void    init_selfie_camera(t_game *game);
int     load_selfie_texture(t_game *game);
void    draw_static_selfie_stick(t_game *game);

/*MAIN*/
int		main(int argc, char **argv);

#endif
