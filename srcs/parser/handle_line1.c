#include "../../cub3d.h"

/* 纹理四个键 */
int	handle_no_line(t_game *g, t_parse *p, const char *s)
{
	if (p->got_no++)
		return (ft_fprintf(2, "Error: Duplicate NO texture in %s\n",
				p->filepath), 0);
	g->textures.no_path = dup_path_strict(s);
	if (!g->textures.no_path)
		return (ft_fprintf(2, "Error: Invalid or missing NO texture in %s\n",
				p->filepath), 0);
	return (1);
}

int	handle_so_line(t_game *g, t_parse *p, const char *s)
{
	if (p->got_so++)
		return (ft_fprintf(2, "Error: Duplicate SO texture in %s\n",
				p->filepath), 0);
	g->textures.so_path = dup_path_strict(s);
	if (!g->textures.so_path)
		return (ft_fprintf(2, "Error: Invalid or missing SO texture in %s\n",
				p->filepath), 0);
	return (1);
}

int	handle_we_line(t_game *g, t_parse *p, const char *s)
{
	if (p->got_we++)
		return (ft_fprintf(2, "Error: Duplicate WE texture in %s\n",
				p->filepath), 0);
	g->textures.we_path = dup_path_strict(s);
	if (!g->textures.we_path)
		return (ft_fprintf(2, "Error: Invalid or missing WE texture in %s\n",
				p->filepath), 0);
	return (1);
}

int	handle_ea_line(t_game *g, t_parse *p, const char *s)
{
	if (p->got_ea++)
		return (ft_fprintf(2, "Error: Duplicate EA texture in %s\n",
				p->filepath), 0);
	g->textures.ea_path = dup_path_strict(s);
	if (!g->textures.ea_path)
		return (ft_fprintf(2, "Error: Invalid or missing EA texture in %s\n",
				p->filepath), 0);
	return (1);
}