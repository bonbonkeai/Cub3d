#include "../../cub3d.h"

// ==================== Minimap瓦片绘制 ====================

// 17. 判断是否为墙壁
int is_wall_tile(char tile)
{
    return (tile == '1');
}

// 18. 判断是否为空地
int is_floor_tile(char tile)
{
    return (tile != '\0' && tile != '1');
}

// 19. 绘制单个地图瓦片
void draw_map_tile(t_game *game, t_tile_pos pos)
{
    t_rect_params tile_rect;
    
    tile_rect.x = game->minimap.offset_x + pos.j * game->minimap.tile_size;
    tile_rect.y = game->minimap.offset_y + pos.i * game->minimap.tile_size;
    tile_rect.width = game->minimap.tile_size;
    tile_rect.height = game->minimap.tile_size;
    if (is_wall_tile(game->map[pos.i][pos.j]))
    {
        tile_rect.color = MM_WALL;
        draw_rect(&game->mlx.img, tile_rect);
    }
    else if (is_floor_tile(game->map[pos.i][pos.j]))
    {
        tile_rect.color = MM_FLOOR;
        draw_rect(&game->mlx.img, tile_rect);
    }
}

// 20. 绘制所有地图瓦片
void draw_map_tiles(t_game *game)
{
    t_tile_pos pos;
    
    pos.i = 0;
    while (pos.i < game->map_height)
    {
        pos.j = 0;
        while (pos.j < game->map_width)
        {
            draw_map_tile(game, pos);
            pos.j++;
        }
        pos.i++;
    }
}