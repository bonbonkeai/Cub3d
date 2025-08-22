#include "../../cub3d.h"

int	init_keys(t_keys *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
    keys->esc = 0;
	return (1);
}
