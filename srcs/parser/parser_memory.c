#include "../../cub3d.h"

void	init_parser(t_parse *p)
{
	p->raw_lines = NULL;
	p->raw_count = 0;
	p->map_started = 0;
	p->fd = -1;
	p->got_no = 0;
	p->got_so = 0;
	p->got_we = 0;
	p->got_ea = 0;
	p->got_f = 0;
	p->got_c = 0;
	p->filepath = NULL;
	p->textures = malloc(sizeof(t_texture));
	if (p->textures)
	{
		p->textures->no_path = NULL;
		p->textures->so_path = NULL;
		p->textures->we_path = NULL;
		p->textures->ea_path = NULL;
		p->textures->floor_color = 0;
		p->textures->ceiling_color = 0;
		p->textures->floor_r = 0;
		p->textures->floor_g = 0;
		p->textures->floor_b = 0;
		p->textures->ceiling_r = 0;
		p->textures->ceiling_g = 0;
		p->textures->ceiling_b = 0;
	}
}

int	ft_free_cub(t_parse *parser, int fd)
{
	if (fd >= 0)
	{
		cleanup_get_next_line(fd);
		close(fd);
	}
	if (parser->textures)
	{
		if (parser->textures->no_path)
			free(parser->textures->no_path);
		if (parser->textures->so_path)
			free(parser->textures->so_path);
		if (parser->textures->we_path)
			free(parser->textures->we_path);
		if (parser->textures->ea_path)
			free(parser->textures->ea_path);
		free(parser->textures);
	}
	if (parser->raw_lines)
		free_raw_lines(parser->raw_lines, parser->raw_count);
	if (fd >= 0)
		close(fd);
	return (0);
}

void	ft_free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_raw_lines(char **lines, int count)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (i < count)
		free(lines[i++]);
	free(lines);
}

int	append_line(char ***arr, int *count, char *line)
{
	char	**tmp;

	if (!arr || !count || !line)
		return (0);
	tmp = ft_realloc(*arr,
			sizeof(char *) * (*count + 1),
			sizeof(char *) * (*count + 2));
	if (!tmp)
		return (0);
	*arr = tmp;
	(*arr)[(*count)++] = line;
	(*arr)[*count] = NULL;
	return (1);
}
