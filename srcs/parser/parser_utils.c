/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:36:47 by jdu               #+#    #+#             */
/*   Updated: 2025/08/26 16:36:48 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	free_raw_lines(char **lines, int count)
{
	int	i;

	if (!lines)
		return;
	i = 0;
	while (i < count)
		free(lines[i++]);
	free(lines);
}

int append_line(char ***arr, int *count, char *line)
{
    char **tmp;

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

void	free_map(char **map)
{
	int	i;

	if (!map)
		return;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

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
}
