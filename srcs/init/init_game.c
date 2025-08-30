/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:32:43 by jdu               #+#    #+#             */
/*   Updated: 2025/08/30 14:15:26 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	init_player_and_textures(t_game *game)
{
	if (!check_and_init_player(game))
		return (ft_fprintf(2, ERR_PLAYER), 0);
	if (!init_texture_defaults(&game->textures) || \
		!init_textures(&game->textures, game->mlx.mlx_ptr))
		return (ft_fprintf(2, ERR_TEX), 0);
	return (1);
}

static int	init_selfie_and_keys(t_game *game)
{
	init_selfie_camera(game);
	if (!load_selfie_texture(game))
	{
		ft_fprintf(2, ERR_SELFIE);
		game->selfie_cam.visible = 0;
		return (0);
	}
	if (!init_keys(&game->keys))
		return (ft_fprintf(2, ERR_KEY), 0);
	return (1);
}

int	init_game(t_game *game, const char *map_path)
{
	game->win_width = WIN_WIDTH;
	game->win_height = WIN_HEIGHT;
	if (!init_mlx(&game->mlx, game->win_width, game->win_height))
		return (ft_fprintf(2, ERR_MLX), 0);
	if (!init_map(game, map_path))
	{
		ft_fprintf(2, "Error: Failed to load map from file '%s'\n", \
			map_path);
		return (0);
	}
	if (!init_player_and_textures(game))
		return (0);
	if (!init_selfie_and_keys(game))
		return (0);
	init_game_structures(game);
	return (1);
}

// int	init_game(t_game *game, const char *map_path)
// {
// 	game->win_width = WIN_WIDTH;
// 	game->win_height = WIN_HEIGHT;
// 	if (!init_mlx(&game->mlx, game->win_width, game->win_height))
// 		return (ft_fprintf(2, ERR_MLX), 0);
// 	if (!init_map(game, map_path))
// 	{
// 		ft_fprintf(2, "Error: Failed to load map from file '%s'\n", map_path);
// 		return (0);
// 	}
// 	if (!check_and_init_player(game))
// 		return (ft_fprintf(2, ERR_PLAYER), 0);
// 	if (!init_texture_defaults(&game->textures) || !init_textures(&game->textures, game->mlx.mlx_ptr))
// 		return (ft_fprintf(2, ERR_TEX), 0);
// 	init_selfie_camera(game);
// 	if (!load_selfie_texture(game))
//     {
//         ft_fprintf(2, ERR_SELFIE);
//         game->selfie_cam.visible = 0;
// 		return (0);
//     }
// 	if (!init_keys(&game->keys))
// 		return (ft_fprintf(2, ERR_KEY), 0);
// 	init_game_structures(game);
// 	return (1);
// }

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
		free_map(game->map);
	free_textures(&game->textures, game->mlx.mlx_ptr);
	if (game->selfie_cam.selfie_texture)
	{
		if (game->selfie_cam.selfie_texture->img_ptr)
			mlx_destroy_image(game->mlx.mlx_ptr, \
					game->selfie_cam.selfie_texture->img_ptr);
		free(game->selfie_cam.selfie_texture);
	}
	free_mlx(&game->mlx);
}

void	free_textures(t_texture *tex, void *mlx_ptr)
{
	free_img(mlx_ptr, &tex->no);
	free_img(mlx_ptr, &tex->so);
	free_img(mlx_ptr, &tex->we);
	free_img(mlx_ptr, &tex->ea);
	if (tex->no_path)
		free(tex->no_path);
	if (tex->so_path)
		free(tex->so_path);
	if (tex->we_path)
		free(tex->we_path);
	if (tex->ea_path)
		free(tex->ea_path);
	tex->no_path = NULL;
	tex->so_path = NULL;
	tex->we_path = NULL;
	tex->ea_path = NULL;
}
