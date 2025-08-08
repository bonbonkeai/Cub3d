#include "cub3d.h"

// int	set_up_game(t_game *game)
// {
// 	mlx_hook(game->mlx.win_ptr, X_EVENT_KEY_PRESS, 0, key_press, game);
//     mlx_hook(game->mlx.win_ptr, X_EVENT_KEY_RELEASE, 0, key_release, game);
//     mlx_hook(game->mlx.win_ptr, X_EVENT_EXIT, 0, exit_button, game);
// 	mlx_loop_hook(game->mlx.mlx_ptr, render_game, game);
// 	render_game(game);
// 	return (1);
// }

int	set_up_game(t_game *game)
{
	// 二次防御：关键资源完整性检查
	if (!game->mlx.mlx_ptr || !game->mlx.win_ptr || !game->mlx.img.img_ptr)
	{
		ft_fprintf(2, "Error: Invalid MLX window or image\n");
		exit_game(game, 1);
	}
	if (!game->textures.no.img_ptr || !game->textures.so.img_ptr ||
		!game->textures.we.img_ptr || !game->textures.ea.img_ptr)
	{
		ft_fprintf(2, "Error: Missing texture(s)\n");
		exit_game(game, 1);
	}
	// 键盘事件
	mlx_hook(game->mlx.win_ptr, X_EVENT_KEY_PRESS, 0, key_press, game);
	mlx_hook(game->mlx.win_ptr, X_EVENT_KEY_RELEASE, 0, key_release, game);
	// 鼠标移动事件
	mlx_hook(game->mlx.win_ptr, 6, 1L << 6, mouse_move, game);
	// 窗口关闭按钮
	mlx_hook(game->mlx.win_ptr, X_EVENT_EXIT, 0, exit_button, game);
	// 启动时隐藏鼠标 + 定位到中心
	mlx_mouse_hide(game->mlx.mlx_ptr, game->mlx.win_ptr);
	mlx_mouse_move(game->mlx.mlx_ptr, game->mlx.win_ptr,
		game->win_width / 2, game->win_height / 2);
	// 主循环渲染钩子
	mlx_loop_hook(game->mlx.mlx_ptr, render_game, game);
	// 先画第一帧
	render_game(game);
	return (1);
}


int	render_game(t_game *game)
{
	// 1. 更新玩家位置和方向
	update_player(game);

	// 2. 清空帧缓冲（而不是直接清窗口）
	clear_image(&game->mlx.img, 0x000000);

	// 3. 先画 3D 场景
	cast_rays(game);   // 你自己的光线投射算法
	// 或者 draw_walls(game);

	// 4. 再画 minimap（覆盖在 3D 上面）
	draw_minimap(game);

	// 5. 画准星（可选）
	draw_crosshair(game);

	// 6. 一次性推送画面到窗口
	mlx_put_image_to_window(game->mlx.mlx_ptr,
							game->mlx.win_ptr,
							game->mlx.img.img_ptr,
							0, 0);

	return (0);
}

// int	render_game(t_game *game)
// {
// 	update_player(game);
// 	mlx_clear_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	
//     //用玩家视角投射光线生成视图（raycasting）
//     // cast_rays(game);
// 	// draw_walls(game);

// 	// minimap：
// 	// draw_minimap(game);
// 	// draw_crosshair(game);

// 	return (0);
// }
