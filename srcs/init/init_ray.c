#include "cub3d.h"

int	init_rays(t_ray **rays, int screen_width)
{
	int		i;
	t_ray	*new_rays;

	new_rays = malloc(sizeof(t_ray) * screen_width);
	if (!new_rays)
		return (0);
	i = 0;
	while (i < screen_width)
	{
		new_rays[i].angle = 0;
		new_rays[i].distance = 0;
		new_rays[i].hit_vertical = 0;
		new_rays[i].texture_id = 0;
		new_rays[i].hit_x = 0;
		new_rays[i].hit_y = 0;
		i++;
	}
	*rays = new_rays;
	return (1);
}

void	free_rays(t_ray **rays)
{
	if (*rays)
	{
		free(*rays);
		*rays = NULL;
	}
}