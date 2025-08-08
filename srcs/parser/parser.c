#include "cub3d.h"

static int	handle_empty_or_gap(t_parse *p, char *trim, const char *filepath)
{
	if (*trim == '\0')
	{
		free(trim);
		if (p->map_started)
		{
			ft_fprintf(2, "Error: Map contains empty line in %s\n", filepath);
			return (0);
		}
		return (1); // 空行但未开始地图，跳过
	}
	return (2); // 非空行
}

static int	parse_header_line(t_game *game, t_parse *p, char *trim)
{
	if (!p->map_started && ft_strncmp(trim, "NO ", 3) == 0)
		return (handle_texture_line(game, trim + 3, &p->got_no, &game->textures.no_path));
	if (!p->map_started && ft_strncmp(trim, "SO ", 3) == 0)
		return (handle_texture_line(game, trim + 3, &p->got_so, &game->textures.so_path));
	if (!p->map_started && ft_strncmp(trim, "WE ", 3) == 0)
		return (handle_texture_line(game, trim + 3, &p->got_we, &game->textures.we_path));
	if (!p->map_started && ft_strncmp(trim, "EA ", 3) == 0)
		return (handle_texture_line(game, trim + 3, &p->got_ea, &game->textures.ea_path));
	if (!p->map_started && ft_strncmp(trim, "F ", 2) == 0)
		return (handle_color_line(trim + 2, &p->got_f, &game->textures.floor_color));
	if (!p->map_started && ft_strncmp(trim, "C ", 2) == 0)
		return (handle_color_line(trim + 2, &p->got_c, &game->textures.ceiling_color));
	return (-1); // 不是头部
}

static int	process_line(t_game *game, t_parse *p, char *line, const char *filepath)
{
	char	*trim;
	int		ret;

	trim = ft_strtrim(line, " \n\t");
	free(line);
	ret = handle_empty_or_gap(p, trim, filepath);
	if (ret != 2)
		return (ret);
	ret = parse_header_line(game, p, trim);
	if (ret == 0)
		return (free(trim), 0);
	if (ret == 1)
		return (free(trim), 1);
	if (is_map_line(trim))
	{
		if (!handle_map_line(trim, &p->raw_lines, &p->raw_count, &p->map_started))
			return (0);
		return (1);
	}
	free(trim);
	ft_fprintf(2, "Error: Invalid line in %s\n", filepath);
	return (0);
}

static int	final_checks(t_game *game, t_parse *p, const char *filepath)
{
	if (!PARSE_GOT_ALL(p))
		return (ft_fprintf(2, "Error: Missing parameters in %s\n", filepath), 0);
	if (!finalize_map(game, p->raw_lines, p->raw_count))
		return (0);
	if (!validate_map(game))
		return (0);
	return (1);
}

int	parse_cub_file(const char *filepath, t_game *game)
{
	t_parse	p;
	char	*line;

	init_parser(&p);
	p.fd = open(filepath, O_RDONLY);
	if (p.fd < 0)
		return (ft_fprintf(2, "Error: Cannot open %s\n", filepath), 0);
	while ((line = get_next_line(p.fd)))
	{
		if (!process_line(game, &p, line, filepath))
			return (close(p.fd), free_raw_lines(p.raw_lines, p.raw_count), 0);
	}
	close(p.fd);
	if (!final_checks(game, &p, filepath))
		return (free_raw_lines(p.raw_lines, p.raw_count), 0);
	free_raw_lines(p.raw_lines, p.raw_count);
	return (1);
}

// int	parse_cub_file(const char *filepath, t_game *game)
// {
// 	int		fd;
// 	char	*line;
// 	char	**raw_lines = NULL;
// 	int		raw_count = 0;
// 	int		got_no = 0, got_so = 0, got_we = 0, got_ea = 0, got_f = 0, got_c = 0;
// 	int		map_started = 0;

// 	fd = open(filepath, O_RDONLY);
// 	if (fd < 0)
// 		return (ft_fprintf(2, "Error: Cannot open %s\n", filepath), 0);
// 	while ((line = get_next_line(fd)))
// 	{
// 		char *trim = ft_strtrim(line, " \n\t");
// 		free(line);

// 		// ---- 空行处理 ----
// 		if (*trim == '\0')
// 		{
// 			free(trim);
// 			if (map_started)
// 				return (close(fd), free_raw_lines(raw_lines, raw_count),
// 					ft_fprintf(2, "Error: Map contains empty line\n"), 0);
// 			continue;
// 		}
// 		// ---- 参数部分（地图开始后禁止出现）----
// 		if (!map_started && ft_strncmp(trim, "NO ", 3) == 0)
// 		{
// 			if (got_no++)
// 				return (free(trim), close(fd), free_raw_lines(raw_lines, raw_count),
// 					ft_fprintf(2, "Error: Duplicate NO texture\n"), 0);
// 			game->textures.no_path = dup_path_strict(trim + 3);
// 			if (!game->textures.no_path)
// 				return (free(trim), close(fd), free_raw_lines(raw_lines, raw_count),
// 					ft_fprintf(2, "Error: Invalid or missing NO texture\n"), 0);
// 		}
// 		else if (!map_started && ft_strncmp(trim, "SO ", 3) == 0)
// 		{
// 			if (got_so++)
// 				return (free(trim), close(fd), free_raw_lines(raw_lines, raw_count),
// 					ft_fprintf(2, "Error: Duplicate SO texture\n"), 0);
// 			game->textures.so_path = dup_path_strict(trim + 3);
// 			if (!game->textures.so_path)
// 				return (free(trim), close(fd), free_raw_lines(raw_lines, raw_count),
// 					ft_fprintf(2, "Error: Invalid or missing SO texture\n"), 0);
// 		}
// 		else if (!map_started && ft_strncmp(trim, "WE ", 3) == 0)
// 		{
// 			if (got_we++)
// 				return (free(trim), close(fd), free_raw_lines(raw_lines, raw_count),
// 					ft_fprintf(2, "Error: Duplicate WE texture\n"), 0);
// 			game->textures.we_path = dup_path_strict(trim + 3);
// 			if (!game->textures.we_path)
// 				return (free(trim), close(fd), free_raw_lines(raw_lines, raw_count),
// 					ft_fprintf(2, "Error: Invalid or missing WE texture\n"), 0);
// 		}
// 		else if (!map_started && ft_strncmp(trim, "EA ", 3) == 0)
// 		{
// 			if (got_ea++)
// 				return (free(trim), close(fd), free_raw_lines(raw_lines, raw_count),
// 					ft_fprintf(2, "Error: Duplicate EA texture\n"), 0);
// 			game->textures.ea_path = dup_path_strict(trim + 3);
// 			if (!game->textures.ea_path)
// 				return (free(trim), close(fd), free_raw_lines(raw_lines, raw_count),
// 					ft_fprintf(2, "Error: Invalid or missing EA texture\n"), 0);
// 		}
// 		else if (!map_started && ft_strncmp(trim, "F ", 2) == 0)
// 		{
// 			if (got_f++)
// 				return (free(trim), close(fd), free_raw_lines(raw_lines, raw_count),
// 					ft_fprintf(2, "Error: Duplicate floor color\n"), 0);
// 			if (!parse_color(trim + 2, &game->textures.floor_color))
// 				return (free(trim), close(fd), free_raw_lines(raw_lines, raw_count),
// 					ft_fprintf(2, "Error: Invalid floor color\n"), 0);
// 		}
// 		else if (!map_started && ft_strncmp(trim, "C ", 2) == 0)
// 		{
// 			if (got_c++)
// 				return (free(trim), close(fd), free_raw_lines(raw_lines, raw_count),
// 					ft_fprintf(2, "Error: Duplicate ceiling color\n"), 0);
// 			if (!parse_color(trim + 2, &game->textures.ceiling_color))
// 				return (free(trim), close(fd), free_raw_lines(raw_lines, raw_count),
// 					ft_fprintf(2, "Error: Invalid ceiling color\n"), 0);
// 		}
// 		// ---- 地图行 ----
// 		else if (is_map_line(trim))
// 		{
// 			if (!append_line(&raw_lines, &raw_count, trim))
//             {
//                 free(trim);
//                 close(fd);
//                 ft_fprintf(2, "Error: Memory allocation failed while parsing map\n");
//                 free_raw_lines(raw_lines, raw_count);
//                 return (0);
//             }
//             map_started = 1;
//             continue ;
// 		}
// 		else
// 		{
// 			free(trim);
// 			return (close(fd), free_raw_lines(raw_lines, raw_count),
// 				ft_fprintf(2, "Error: Invalid line in %s\n", filepath), 0);
// 		}
// 		free(trim);
// 	}
// 	close(fd);
// 	if (!(got_no && got_so && got_we && got_ea && got_f && got_c))
// 		return (free_raw_lines(raw_lines, raw_count),
// 			ft_fprintf(2, "Error: Missing parameters in %s\n", filepath), 0);
// 	if (!normalize_map(game, raw_lines, raw_count))
// 		return (free_raw_lines(raw_lines, raw_count),
// 			ft_fprintf(2, "Error: Failed to normalize map\n"), 0);
//     if (!check_and_init_player(game))
//     {
//         free_raw_lines(raw_lines, raw_count);
//         ft_fprintf(2, "Error: Map must contain exactly one player start position\n");
//         return (0);
//     }
//     if (!check_map_closed(game))
//     {
//         free_raw_lines(raw_lines, raw_count);
//         ft_fprintf(2, "Error: Map is not closed\n");
//         return (0);
//     }
// 	return (1);
// }

