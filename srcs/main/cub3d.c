#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;
    char    **map;

	if (argc != 2)
	{
		ft_fprintf(2, "Usage: ./cub3D map.cub\n");
		return (1);
	}
	map = parse_map(argv[1], &game);
	if (!map)
		return (1);
	init_game(&game, map, get_map_width(map), get_map_height(map));
    //
    //先测试一下是否可以打开窗口
    mlx_put_image_to_window(game->mlx.mlx_ptr,
                            game->mlx.win_ptr,
                            game->mlx.frame.img_ptr, 0, 0);
    mlx_loop(game->mlx.mlx_ptr);
    //
	game_loop(&game);
	free_game(&game);
	return (0);
}
