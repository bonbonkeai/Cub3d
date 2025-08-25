#include "../../cub3d.h"

// int	init_game(t_game *game, char **map, int width, int height)
// {
// 	game->map = map;
// 	game->map_width = width;
// 	game->map_height = height;
// 	game->win_width = WIN_WIDTH;
// 	game->win_height = WIN_HEIGHT;
// 	if (!init_mlx(&game->mlx, game->win_width, game->win_height))
// 	    return (0);
// 	if (!init_player(&game->player, game->map))
// 		return (0);
// 	if (!init_textures(&game->textures, game->mlx.mlx_ptr))
// 		return (0);
// 	if (!init_keys(&game->keys))
// 		return (0);
// 	if (!init_rays(&game->rays, game->win_width))
// 		return (0);
// 	return (1);
// }

// int	init_game(t_game *game, char **map, int map_width, int map_height)
// {
// 	game->map = map;
// 	game->map_width = map_width;
// 	game->map_height = map_height;
// 	game->win_width = WIN_WIDTH;
// 	game->win_height = WIN_HEIGHT;
//     game->shadow_factor = 0.7;
// 	if (!init_mlx(&game->mlx, game->win_width, game->win_height))
// 	{
// 		ft_fprintf(2, "Error: Failed to initialize mlx\n");
// 		exit_game(game, 1);
// 	}
// 	if (!init_player(&game->player, game->map))
// 	{
// 		ft_fprintf(2, "Error: Failed to initialize player position\n");
// 		exit_game(game, 1);
// 	}
// 	if (!init_textures(&game->textures, game->mlx.mlx_ptr))
// 	{
// 		ft_fprintf(2, "Error: Failed to load textures\n");
// 		exit_game(game, 1);
// 	}
// 	if (!init_keys(&game->keys))
// 	{
// 		ft_fprintf(2, "Error: Failed to initialize keys\n");
// 		exit_game(game, 1);
// 	}
// 	if (!init_rays(&game->rays, game->win_width))
// 	{
// 		ft_fprintf(2, "Error: Failed to initialize rays\n");
// 		exit_game(game, 1);
// 	}
// 	return (1);
// }

int create_test_map(t_game *game)
{
    int i, j;
    
    // 设置地图尺寸
    game->map_width = 8;
    game->map_height = 8;
    printf("Creating test map: %dx%d\n", game->map_width, game->map_height);
    // 分配地图内存
    game->map = malloc(sizeof(char *) * game->map_height);
    if (!game->map)
    {
        printf("Failed to allocate map rows\n");
        return (0);
    }
    for (i = 0; i < game->map_height; i++)
    {
        game->map[i] = malloc(sizeof(char) * (game->map_width + 1));
        if (!game->map[i])
        {
            ft_printf("Failed to allocate map row %d\n", i);
            for (j = 0; j < i; j++)
                free(game->map[j]);
            free(game->map);
            return (0);
        }
        // 初始化为墙
        ft_memset(game->map[i], '1', game->map_width);
        game->map[i][game->map_width] = '\0';
    }
    // 创建简单的测试地图
    for (i = 1; i < game->map_height - 1; i++)
    {
        for (j = 1; j < game->map_width - 1; j++)
        {
            game->map[i][j] = '0'; // 空地
        }
    }
    // 在中央放置玩家起始位置（朝北）
    if (game->map_height > 5 && game->map_width > 5)
    {
        game->map[5][5] = 'N'; // 玩家起始位置
        ft_printf("Placed player 'N' at position [5][5]\n");
    }
    else
    {
        // 如果地图太小，放在 (1,1)
        game->map[1][1] = 'N';
        ft_printf("Placed player 'N' at position [1][1]\n");
    }
    // 打印地图用于调试
    ft_printf("Created test map:\n");
    for (i = 0; i < game->map_height; i++)
    {
        ft_printf("Row %d: %s\n", i, game->map[i]);
    }
    return (1);
}

int	init_game(t_game *game)
{
	game->win_width = WIN_WIDTH;
	game->win_height = WIN_HEIGHT;
	game->shadow_factor = 0.7;
	if (!init_mlx(&game->mlx, game->win_width, game->win_height))
	{
		ft_fprintf(2, "Error: Failed to initialize mlx\n");
		// exit_game(game, 1);
		return (-1);
	}
	if (!create_test_map(game))
	{
		ft_fprintf(2, "Error: Failed to create test map\n");
		return (0);
	}
	if (!check_and_init_player(game))
	{
		ft_fprintf(2, "Error: Failed to initialize player\n");
		return (0);
	}
	if (!init_texture_defaults(&game->textures))
	{
		// exit_game(game, 1);
		return (0);
	}
	// if (!init_textures(&game->textures, game->mlx.mlx_ptr))
	// {
	// 	ft_fprintf(2, "Error: Failed to load textures\n");
	// 	// exit_game(game, 1);
	// 	return (0);
	// }
	if (!init_keys(&game->keys))
	{
		ft_fprintf(2, "Error: Failed to initialize keys\n");
		// exit_game(game, 1);
		return (0);
	}
	if (!init_rays(&game->rays, game->win_width))
	{
		ft_fprintf(2, "Error: Failed to initialize rays\n");
		// exit_game(game, 1);
		return (0);
	}
	return (1);
}

void	free_game(t_game *game)
{
	if (game->map)
		free_map(game->map);
	if (game->rays)
		free_rays(&game->rays);
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

// int	exit_game(t_game *game, int exit_code)
// {
// 	if (game->mlx.mlx_ptr)
// 		mlx_loop_end(game->mlx.mlx_ptr);
// 	free_game(game);
// 	exit(exit_code);
// }