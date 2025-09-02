/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_valid_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclee <niclee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:47:24 by niclee            #+#    #+#             */
/*   Updated: 2025/09/02 15:47:24 by niclee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	validate_map_closed(char **map, int height, int width)
{
	int	i;
	int	j;

	if (!map || height <= 0 || width <= 0)
		return (0);
	j = 0;
	while (j < width)
	{
		if (!map[0] || !map[height - 1])
			return (0);
		if (map[0][j] != '1' && map[0][j] != ' ')
			return (0);
		if (map[height - 1][j] != '1' && map[height - 1][j] != ' ')
			return (0);
		j++;
	}
	i = 0;
	while (i < height)
	{
		if (!map[i])
			return (0);
		if (map[i][0] != '1' && map[i][0] != ' ')
			return (0);
		if (map[i][width - 1] != '1' && map[i][width - 1] != ' ')
			return (0);
		i++;
	}
	i = 1;
	while (i < height - 1)
	{
		if (!map[i])
			return (0);
		j = 1;
		while (j < width - 1)
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' '
					|| map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	count_players(char **map, int height, int width)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	if (!map || height <= 0 || width <= 0)
		return (0);
	i = 0;
	while (i < height)
	{
		if (!map[i])
			return (0);
		j = 0;
		while (j < width)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	validate_and_process_map(t_parse *parser, t_game *game)
{
	if (parser->raw_count == 0 || !parser->raw_lines)
		return (error_msg("No map found"));
	if (!normalize_map(game, parser->raw_lines, parser->raw_count))
		return (error_msg("Failed to normalize map"));
	if (count_players(game->map, game->map_height, game->map_width) != 1)
		return (error_msg("Map must have exactly one player"));
	if (!validate_map_closed(game->map, game->map_height, game->map_width))
		return (error_msg("Map is not properly closed"));
	return (1);
}
