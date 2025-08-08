#include "cub3d.h"

// 处理纹理行
int	handle_texture_line(t_game *game, const char *trim, int *got_flag, char **dst)
{
	if ((*got_flag)++)
		return (ft_fprintf(2, "Error: Duplicate texture\n"), 0);
	*dst = dup_path_strict(trim);
	if (!*dst)
		return (ft_fprintf(2, "Error: Invalid or missing texture\n"), 0);
	return (1);
}
// 处理颜色行
int	handle_color_line(const char *trim, int *got_flag, int *dst_color)
{
	if ((*got_flag)++)
		return (ft_fprintf(2, "Error: Duplicate color\n"), 0);
	if (!parse_color(trim, dst_color))
		return (ft_fprintf(2, "Error: Invalid color\n"), 0);
	return (1);
}
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
int	finalize_map(t_game *game, char **raw_lines, int raw_count)
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