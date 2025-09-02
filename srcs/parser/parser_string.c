/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclee <niclee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:47:16 by niclee            #+#    #+#             */
/*   Updated: 2025/09/02 15:47:16 by niclee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	*trim_whitespace(char *str)
{
	char	*start;
	char	*end;
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	start = str;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	if (*start == '\0')
		return (ft_strdup(""));
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	len = end - start + 1;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, start, len);
	result[len] = '\0';
	return (result);
}

int	is_empty_line(const char *line)
{
	if (!line)
		return (1);
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

int	is_texture(const char *line)
{
	if (!line)
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	return (0);
}

int	is_color(const char *line)
{
	if (!line)
		return (0);
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

int	error_msg(const char *msg)
{
	ft_fprintf(2, "Error\n%s\n", msg);
	return (0);
}
