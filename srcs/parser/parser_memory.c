/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclee <niclee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:47:12 by niclee            #+#    #+#             */
/*   Updated: 2025/09/02 15:47:12 by niclee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
