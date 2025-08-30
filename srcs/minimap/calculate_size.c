#include "../../cub3d.h"

// int	minimap_tile_size(t_game *g)
// {
// 	int	max_w;
// 	int	max_h;
// 	int	tw;
// 	int	th;
// 	int	tile;

// 	max_w = g->win_width / 3;
// 	max_h = g->win_height / 3;
// 	if (g->map_width <= 0 || g->map_height <= 0)
// 		return (4);
// 	tw = max_w / g->map_width;
// 	th = max_h / g->map_height;
// 	tile = tw;
// 	if (th < tile)
// 		tile = th;
// 	if (tile < 2)
// 		tile = 2;
// 	return (tile);
// }

// 7. 计算最大允许尺寸
void calculate_max_minimap_size(t_game *game, int *max_w, int *max_h)
{
    *max_w = game->win_width / 3;
    *max_h = game->win_height / 3;
}

// 8. 计算瓦片尺寸
void calculate_tile_dimensions(t_game *game, t_tile_calc *calc)
{
    if (!game || !calc)
        return;
    if (game->map_width <= 0 || game->map_height <= 0)
    {
        calc->tw = 4;
        calc->th = 4;
        return;
    }
    calc->tw = calc->max_w / game->map_width;
    calc->th = calc->max_h / game->map_height;
}

// 9. 选择最小瓦片尺寸
int select_minimum_tile_size(int tw, int th)
{
    int tile;
    
    tile = tw;
    if (th < tile)
        tile = th;
    if (tile < 2)
        tile = 2;
    return (tile);
}

// 10. 计算minimap瓦片大小
int minimap_tile_size(t_game *game)
{
    t_tile_calc calc;
    
    calculate_max_minimap_size(game, &calc.max_w, &calc.max_h);
    calculate_tile_dimensions(game, &calc);
    return (select_minimum_tile_size(calc.tw, calc.th));
}