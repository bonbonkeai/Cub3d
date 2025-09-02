/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_valid_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclee <niclee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:47:22 by niclee            #+#    #+#             */
/*   Updated: 2025/09/02 15:47:22 by niclee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_valid_texture_extension(const char *path)
{
	int	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (ft_strncmp(path + len - 4, ".xpm", 4) == 0
		|| ft_strncmp(path + len - 4, ".XPM", 4) == 0)
		return (1);
	return (0);
}

int	is_file_accessible(const char *path)
{
	int	fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	char_valid(t_parse *parser)
{
	if (!parser->got_no || !parser->got_so || !parser->got_we
		|| !parser->got_ea || !parser->got_f || !parser->got_c)
	{
		return (error_msg("Missing configuration elements"));
	}
	return (1);
}
