#ifndef CUB3D_H
# define CUB3D_H

# include "../Libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <stdlib.h>
# include "../mlx_linux/mlx.h"

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
# define TEX_NORTH "textures/north.xpm"
# define TEX_SOUTH "textures/south.xpm"
# define TEX_EAST  "textures/east.xpm"
# define TEX_WEST  "textures/west.xpm"

/*EVEN*/
# define X_EVENT_KEY_PRESS    2
# define X_EVENT_KEY_RELEASE  3
# define X_EVENT_EXIT         17

# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.05

typedef struct s_img
{
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;


typedef struct s_player
{
	double x;
	double y;
	double dir_x;
	double dir_y;
	double plane_x;
    double plane_y;
    double camera_x;
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
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
	int		floor_color;
	int		ceiling_color;
}	t_texture;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	esc;
}	t_keys;


typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img   img;
}	t_mlx;

typedef struct s_game 
{
	t_mlx		mlx;
	t_player	player;
	t_keys		keys;
	t_texture		textures;
	char		**map;
	int			map_width;
	int			map_height;
	int			win_width;
	int			win_height;
	t_ray		*rays;
}	t_game;

/*INIT && FREE*/
int	init_game(t_game *game, char **map, int width, int height);
void	free_game(t_game *game);
int	exit_game(t_game *game, int exit_code);
int	init_img(void *mlx, t_img *img, int width, int height);
void	free_img(void *mlx_ptr, t_img *img);
int	init_keys(t_keys *keys);
int	init_mlx(t_mlx *mlx, int width, int height);
void	free_mlx(t_mlx *mlx);
int	init_rays(t_ray **rays, int screen_width);
void	free_rays(t_ray **rays);
int	init_texture_img(void *mlx_ptr, t_img *img, char *path);
int	init_textures(t_texture *tex, void *mlx_ptr);
void	free_textures(t_texture *tex, void *mlx_ptr);

int	is_map_line(char *line);
int	get_map_width(char **map);
int	get_map_height(char **map);
int	normalize_map(t_game *game, char **raw_lines, int line_count);
int	init_map(t_game *game, const char *filepath);
void	free_map(char **map);

#endif