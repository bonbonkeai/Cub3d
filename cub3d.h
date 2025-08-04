#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>

typedef struct s_image
{
	char *data;
	int width;
	int height;
}              t_image;

typedef struct s_player
{
	double x;
	double y;
	double dir_x;
	double dir_y;
	double view;
}              t_player;

typedef struct s_ray
{
	double angle;
	double cible_x;
	double ciblde_y;
}			t_ray;

typedef struct s_texture
{
	t_image no;
	t_image so;
	t_image we;
	t_image ea;
}			t_texture;

typedef struct s_keys
{
	int w;
	int a;
	int s;
	int d;
	int left;
	int right;
}			t_keys;

type struct s_game
{
	t_player player;
	t_keys keys;
	char **map;
	t_ray ray;
	t_texture texture;

}		t_game;


#endif