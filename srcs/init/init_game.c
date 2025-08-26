/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:32:43 by jdu               #+#    #+#             */
/*   Updated: 2025/08/26 16:32:45 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	init_game(t_game *game, const char *map_path)
{
	game->win_width = WIN_WIDTH;
	game->win_height = WIN_HEIGHT;
	if (!init_mlx(&game->mlx, game->win_width, game->win_height))
		return (ft_fprintf(2, "Error: Failed to initialize mlx\n"), 0);
    if (!init_map(game, map_path))
		return (ft_fprintf(2, "Error: Failed to load map from file '%s'\n", map_path), 0);
	if (!check_and_init_player(game))
		return (ft_fprintf(2, "Error: Failed to initialize player\n"), 0);
	if (!init_texture_defaults(&game->textures) ||
		!init_textures(&game->textures, game->mlx.mlx_ptr))
		return (ft_fprintf(2, "Error: Failed to load textures\n"), 0);
	if (!init_keys(&game->keys))
		return (ft_fprintf(2, "Error: Failed to initialize keys\n"), 0);
	return (1);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
		free_map(game->map);
	free_textures(&game->textures, game->mlx.mlx_ptr);
	free_mlx(&game->mlx);
}

int	exit_game(t_game *game, int exit_code)
{
    free_game(game);
	if (game->mlx.mlx_ptr)
	{
		mlx_destroy_display(game->mlx.mlx_ptr);
		free(game->mlx.mlx_ptr);
		game->mlx.mlx_ptr = NULL;
	}
	exit(exit_code);
}
