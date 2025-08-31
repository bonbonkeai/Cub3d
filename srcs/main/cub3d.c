/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:34:08 by jdu               #+#    #+#             */
/*   Updated: 2025/08/31 15:34:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
	{
		ft_fprintf(2, "Usage: ./cub3D map.cub\n");
		return (1);
	}
	if (!parse_file(argv[1], &game))
	{    
		free_game(&game);
		return (1);
	}
	if (!init_game(&game))
	{
		free_game(&game);
		return (1);
	}
	// if (!init_game(&game, argv[1]))
	// {
	// 	free_game(&game);
	// 	return (1);
	// }
	ft_printf("Game initialized successfully, calling set_up_game...\n");
	set_up_game(&game);
	ft_printf("set_up_game completed, starting MLX loop...\n");
	mlx_loop(game.mlx.mlx_ptr);
	return (0);
}
