/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:35:44 by jdu               #+#    #+#             */
/*   Updated: 2025/08/30 14:58:04 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_up_game(t_game *game)
{	
	// 键盘事件
	mlx_hook(game->mlx.win_ptr, EVENT_KEY_PRESS, 1L << 0, key_press, game);
	mlx_hook(game->mlx.win_ptr, EVENT_KEY_RELEASE, 1L << 1, key_release, game);
	// 鼠标移动事件
	mlx_hook(game->mlx.win_ptr, 6, 1L << 6, mouse_move, game);
	// 窗口关闭按钮
	mlx_hook(game->mlx.win_ptr, EVENT_EXIT, 0, exit_button, game);
	// 启动时隐藏鼠标 + 定位到中心
	// mlx_mouse_hide(game->mlx.mlx_ptr, game->mlx.win_ptr);
	mlx_mouse_move(game->mlx.mlx_ptr, game->mlx.win_ptr, \
			game->win_width / 2, game->win_height / 2);
	mlx_loop_hook(game->mlx.mlx_ptr, render_game, game);
	render_game(game);
}

// int	set_up_game(t_game *game)
// {
// 	if (!game->mlx.mlx_ptr || !game->mlx.win_ptr || !game->mlx.img.img_ptr)
// 	{
// 		ft_fprintf(2, "Error: Invalid MLX window or image\n");
// 		return (0);
// 	}
// 	// if (!game->textures.no.img_ptr || !game->textures.so.img_ptr ||
// 	// 	!game->textures.we.img_ptr || !game->textures.ea.img_ptr)
// 	// {
// 	// 	ft_fprintf(2, "Error: Missing texture(s)\n");
// 	// 	return (0);
// 	// }
// 	// 键盘事件
// 	mlx_hook(game->mlx.win_ptr, X_EVENT_KEY_PRESS, 1L << 0, key_press, game);
// mlx_hook(game->mlx.win_ptr, X_EVENT_KEY_RELEASE, 1L << 1, key_release, game);
// 	// 鼠标移动事件
// 	mlx_hook(game->mlx.win_ptr, 6, 1L << 6, mouse_move, game);
// 	// 窗口关闭按钮
// 	mlx_hook(game->mlx.win_ptr, X_EVENT_EXIT, 0, exit_button, game);
// 	// 启动时隐藏鼠标 + 定位到中心
// 	mlx_mouse_hide(game->mlx.mlx_ptr, game->mlx.win_ptr);
// 	mlx_mouse_move(game->mlx.mlx_ptr, game->mlx.win_ptr,
// 		game->win_width / 2, game->win_height / 2);
// 	// 主循环渲染钩子
// 	mlx_loop_hook(game->mlx.mlx_ptr, render_game, game);
// 	// 先画第一帧
// 	render_game(game);
// 	return (1);
// }

int	render_game(t_game *game)
{
	// 1. 更新玩家位置和方向
	update_player(game);
	// 2. 清空帧缓冲（而不是直接清窗口）
	clear_image(&game->mlx.img, 0x000000);
	//画天空和地面
	// draw_floor_and_ceiling(game);
	// 3. 先画 3D 场景
	cast_rays(game); // 光线投射算法
	// 4. 再画 minimap（覆盖在 3D 上面）
	if (game->map)
		draw_minimap(game);
	// 5. 画准星
	draw_crosshair(game);
	// 6. 一次性推送画面到窗口
	draw_static_selfie_stick(game);
	// 7. 自拍杆
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, \
			game->mlx.img.img_ptr, 0, 0);
	return (0);
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
