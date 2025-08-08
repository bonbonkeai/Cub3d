#include "cub3d.h"

static int	is_valid_color(int val)
{
	return (val >= 0 && val <= 255);
}

static void free_split(char **arr)
{
    int i;
    
    i = 0;
    if (!arr)
        return;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

int	parse_color(char *trim, int *r, int *g, int *b)
{
	char	**parts;
	int		count;

	if (!trim || !r || !g || !b)
		return (0);
	parts = ft_split(trim, ',');
	if (!parts)
		return (0);
	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
	{
		free_split(parts);
		return (0);
	}
	*r = ft_atoi(parts[0]);
	*g = ft_atoi(parts[1]);
	*b = ft_atoi(parts[2]);
	free_split(parts);
	if (!is_valid_color(*r) || !is_valid_color(*g) || !is_valid_color(*b))
		return (0);
	return (1);
}

/* 颜色两个键 */
int	handle_floor_line(t_game *g, t_parse *p, const char *s)
{
	if (p->got_f)
		return (ft_fprintf(2, "Error: Duplicate floor color in %s\n",
				p->filepath), 0);
	if (!parse_color((char *)s, &g->textures.floor_r,
			&g->textures.floor_g, &g->textures.floor_b))
		return (ft_fprintf(2, "Error: Invalid floor color in %s\n",
				p->filepath), 0);
	g->textures.floor_color = (g->textures.floor_r << 16)
		| (g->textures.floor_g << 8) | g->textures.floor_b;
	p->got_f = 1;
	return (1);
}

int	handle_ceiling_line(t_game *g, t_parse *p, const char *s)
{
	if (p->got_c)
		return (ft_fprintf(2, "Error: Duplicate ceiling color in %s\n",
				p->filepath), 0);
	if (!parse_color((char *)s, &g->textures.ceiling_r,
			&g->textures.ceiling_g, &g->textures.ceiling_b))
		return (ft_fprintf(2, "Error: Invalid ceiling color in %s\n",
				p->filepath), 0);
	g->textures.ceiling_color = (g->textures.ceiling_r << 16)
		| (g->textures.ceiling_g << 8) | g->textures.ceiling_b;
	p->got_c = 1;
	return (1);
}
