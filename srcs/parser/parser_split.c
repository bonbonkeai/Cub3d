#include "../../cub3d.h"

// 处理地图行
int	handle_map_line(char *trim, char ***raw_lines, int *raw_count, int *map_started)
{
	if (!append_line(raw_lines, raw_count, trim))
	{
		free(trim);
		ft_fprintf(2, "Error: Memory allocation failed while parsing map\n");
		return (0);
	}
	*map_started = 1;
	return (1);
}

// 最终地图处理：标准化 + 玩家初始化
int finalize_map(t_game *game, char **raw_lines, int raw_count)
{
	if (!normalize_map(game, raw_lines, raw_count))
		return (ft_fprintf(2, "Error: Failed to normalize map\n"), 0);
	if (!check_and_init_player(game))
		return (ft_fprintf(2, "Error: Map must contain exactly one player start position\n"), 0);
	return (1);
}

// 地图最终验证（封闭性等）
int	validate_map(t_game *game)
{
	if (!check_map_closed(game))
		return (ft_fprintf(2, "Error: Map is not closed\n"), 0);
	return (1);
}

int	handle_empty_or_gap(t_parse *p, char *trim)
{
	if (*trim == '\0')
	{
		free(trim);
		if (p->map_started)
		{
			ft_fprintf(2, "Error: Map contains empty line in %s\n", p->filepath);
			return (0);
		}
		return (1);
	}
	return (2);
}