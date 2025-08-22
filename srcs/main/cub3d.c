#include "../../cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_fprintf(2, "Usage: ./cub3D map.cub\n");
		return (1);
	}
	(void)argv;
    // if (!parse_cub_file(argv[1], &game))
    // {    
	// 	free_game(&game);
	// 	return (1);
	// }
    if (!init_game(&game))
    {
		free_game(&game);
		return (1);
	}
	set_up_game(&game);
	mlx_loop(game.mlx.mlx_ptr);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	t_game	game;
// 	char	**map;
// 	int		width;
// 	int		height;

// 	if (argc != 2)
// 	{
// 		ft_fprintf(2, "Usage: ./cub3D map.cub\n");
// 		return (1);
// 	}
// 	// 1. 解析地图（parser 独立）
// 	map = parse_map(argv[1], &game);
// 	if (!map)
// 	{
// 		ft_fprintf(2, "Error: invalid map file or parsing failed\n");
// 		return (1);
// 	}
// 	width = get_map_width(map);
// 	height = get_map_height(map);
// 	// 2. 初始化游戏（传入已解析的 map）
// 	if (!init_game(&game, map, width, height))
// 	{
// 		ft_fprintf(2, "Error: game initialization failed\n");
// 		free_map(map); // init_game 失败时释放 parser 分配的 map
// 		return (1);
// 	}
// 	// 3. 设置事件和渲染循环
// 	if (!set_up_game(&game))
// 	{
// 		exit_game(&game, 1); // 用统一的退出逻辑
// 	}
// 	// 4. 进入事件循环
// 	mlx_loop(game.mlx.mlx_ptr);
// 	return (0);
// }

