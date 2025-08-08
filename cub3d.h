#ifndef CUB3D_H
# define CUB3D_H

# include "../Libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include "../minilibx-linux/mlx.h"

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
# define KEY_LEFT_BRACKET   33  // [
# define KEY_RIGHT_BRACKET  30  // ]


/*TEXTURE*/
# define TEXTURE_SIZE 256

/*EVEN*/
# define X_EVENT_KEY_PRESS    2
# define X_EVENT_KEY_RELEASE  3
# define X_EVENT_EXIT         17

# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.05

/*MINIMAP*/
# define MM_WALL    0x30303A
# define MM_FLOOR   0x70707A
# define MM_PLAYER  0xFF4040
# define MM_BORDER  0x202024
# define MM_ARROW   0xFFAA00

/*CROSS*/
# define CROSS_COLOR 0x00FF00 // 绿色
# define CROSS_ALPHA 0.6      // 半透明 60%
# define GAP         6        // 中心到短线起点的距离
# define LINE_LEN    8        // 短线长度
# define DOT_RADIUS  2        // 中心圆点半径 

# define PARSE_GOT_ALL(p) \
	((p)->got_no && (p)->got_so && (p)->got_we && \
	 (p)->got_ea && (p)->got_f  && (p)->got_c)


# define M_PI 3.14159265358979323846

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

typedef struct s_ray
{
	double		angle;
	double		distance;
	int			hit_vertical;
	int			texture_id;
	double		hit_x;
	double		hit_y;
}	t_ray;

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
	t_ray		*rays;
	double  	shadow_factor; // 阴影亮度系数，范围 0.0 ~ 1.0
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



/*PARSER*/
int		parse_cub_file(const char *filepath, t_game *game);
int 	parse_color(const char *str, int *out_color);
int		check_texture_file(const char *path);
char	*dup_path_strict(const char *str);
void	free_raw_lines(char **lines, int count);
int 	check_map_closed(t_game *game);
int 	check_single_player_start(t_game *game);
int		append_line(char ***arr, int *count, char *line);
int		is_map_line(const char *line);
int		get_map_width(char **map);
int		get_map_height(char **map);
int		normalize_map(t_game *game, char **raw_lines, int line_count);
int		init_map(t_game *game, const char *filepath);
void	free_map(char **map);
// int	init_player(t_player *player, char **map);
int		check_and_init_player(t_game *game);
int		handle_map_line(char *trim, char ***raw_lines, int *raw_count, int *map_started);
int		finalize_map(t_game *game, char ***raw_lines, int raw_count);
int		validate_map(t_game *game);
void	init_parser(t_parse *p);
int		handle_no_line(t_game *g, t_parse *p, const char *s);
int		handle_so_line(t_game *g, t_parse *p, const char *s);
int		handle_we_line(t_game *g, t_parse *p, const char *s);
int		handle_ea_line(t_game *g, t_parse *p, const char *s);
int		handle_empty_or_gap(t_parse *p, char *trim);
int		handle_floor_line(t_game *g, t_parse *p, const char *s);
int		handle_ceiling_line(t_game *g, t_parse *p, const char *s);

/*INIT && FREE*/
// int	init_game(t_game *game, char **map, int width, int height);
int		init_game(t_game *game);
void	free_game(t_game *game);
int		exit_game(t_game *game, int exit_code);
int		init_img(void *mlx, t_img *img, int width, int height);
void	free_img(void *mlx_ptr, t_img *img);
int		init_keys(t_keys *keys);
int		init_mlx(t_mlx *mlx, int width, int height);
void	free_mlx(t_mlx *mlx);
int		init_rays(t_ray **rays, int screen_width);
void	free_rays(t_ray **rays);
int		init_texture_img(void *mlx_ptr, t_img *img, char *path);
int		init_textures(t_texture *tex, void *mlx_ptr);
void	free_textures(t_texture *tex, void *mlx_ptr);

/*SETUP*/
void	rotate_player(t_player *p, double angle);
void	update_player(t_game *game);
void	clear_image(t_img *img, int color);
int		set_up_game(t_game *game);
int		render_game(t_game *game);

/*KEY*/
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		exit_button(t_game *game);

/*MINIMAP*/
void	put_px(t_img *img, int x, int y, int color);
void	draw_rect(t_img *img, int x, int y, int w, int h, int color);
void	draw_line(t_img *img, int x0, int y0, int x1, int y1, int color);
int		minimap_tile_size(t_game *g);
void	draw_border(t_img *img, int x, int y, int w, int h, int color);
void	draw_minimap(t_game *game);

/*RAYCASTING*/
void	cast_rays(t_game *game);

/*MAIN*/
int		main(int argc, char **argv);

#endif