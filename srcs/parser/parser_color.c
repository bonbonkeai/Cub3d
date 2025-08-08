#include "cub3d.h"

int parse_color(const char *str, int *out_color)
{
    int     r, g, b;
    char    *trim, *endptr;

    trim = ft_strtrim(str, " \t\n");
    if (!trim || *trim == '\0')
        return (free(trim), 0);
    // 用 sscanf 解析，同时保留剩余内容到 endptr
    char extra[256];
    if (sscanf(trim, "%d,%d,%d", &r, &g, &b) != 3)
    return (free(trim), 0);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (free(trim), 0);
    // 再检查是否有多余字符
    char *comma3 = ft_strchr(trim, ',');
    if (comma3) comma3 = ft_strchr(comma3 + 1, ',');
    if (comma3 && *(comma3 + 1) != '\0')
    {
        char *rest = ft_strtrim(comma3 + 1, "0123456789 \t\n");
        if (*rest != '\0') // 有非空白多余字符
            return (free(rest), free(trim), 0);
        free(rest);
    }
    return (1);
}