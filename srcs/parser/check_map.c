#include "../../cub3d.h"

static int flood_fill(char **map, int y, int x, t_game *game)
{
    if (y < 0 || y >= game->map_height || x < 0 || x >= game->map_width)
        return (0); // 越界，地图不封闭

    if (map[y][x] == ' ' || map[y][x] == '\0')
        return (0); // 访问到空白或非法区域，不封闭

    if (map[y][x] == '1' || map[y][x] == 'x')
        return (1); // 墙或已访问，安全返回

    map[y][x] = 'x'; // 标记访问过

    // 递归检查四个方向
    if (!flood_fill(map, y + 1, x, game)) return 0;
    if (!flood_fill(map, y - 1, x, game)) return 0;
    if (!flood_fill(map, y, x + 1, game)) return 0;
    if (!flood_fill(map, y, x - 1, game)) return 0;

    return 1;
}

int check_map_closed(t_game *game)
{
    char **map_copy;
    int i, j;
    int player_x = (int)(game->player.x);
    int player_y = (int)(game->player.y);

    // 复制地图
    map_copy = malloc(sizeof(char *) * (game->map_height + 1));
    if (!map_copy) return 0;

    for (i = 0; i < game->map_height; i++)
    {
        map_copy[i] = malloc(game->map_width + 1);
        if (!map_copy[i]) {
            while (--i >= 0) free(map_copy[i]);
            free(map_copy);
            return 0;
        }
        for (j = 0; j < game->map_width; j++)
            map_copy[i][j] = game->map[i][j];
        map_copy[i][game->map_width] = '\0';
    }
    map_copy[game->map_height] = NULL;

    // 执行 flood fill
    int res = flood_fill(map_copy, player_y, player_x, game);

    // 释放复制地图
    for (i = 0; i < game->map_height; i++)
        free(map_copy[i]);
    free(map_copy);

    return res;
}
