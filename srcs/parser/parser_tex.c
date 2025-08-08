#include "cub3d.h"

int	check_texture_file(const char *path)
{
	int fd;
    
    fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

char	*dup_path_strict(const char *str)
{
	char	*trim;
	char	*space;

	trim = ft_strtrim(str, " \n\t");
	if (!trim || *trim == '\0')
	{
		free(trim);
		return (NULL);
	}
	// 检查路径中是否包含多余内容
	space = ft_strchr(trim, ' ');
	if (space && *space != '\0')
	{
		// 允许路径后面都是空格/换行，否则报错
		while (*space == ' ' || *space == '\t' || *space == '\n')
			space++;
		if (*space != '\0') // 有多余内容
		{
			free(trim);
			return (NULL);
		}
	}
	// 检查文件是否存在
	if (!check_texture_file(trim))
	{
		free(trim);
		return (NULL);
	}
	return (trim);
}

