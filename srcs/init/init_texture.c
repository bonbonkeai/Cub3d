#include "../../cub3d.h"

// void    init_texture_defaults(t_texture *tex)
// {
//     tex->no.img_ptr = NULL;
//     tex->so.img_ptr = NULL;
//     tex->we.img_ptr = NULL;
//     tex->ea.img_ptr = NULL;
//     tex->no.data = NULL;
//     tex->so.data = NULL;
//     tex->we.data = NULL;
//     tex->ea.data = NULL;
//     tex->no_path = NULL;
//     tex->so_path = NULL;
//     tex->we_path = NULL;
//     tex->ea_path = NULL;
// 	// 临时使用纯色代替纹理（修改 init_textures 函数或创建简单的 1x1 XPM）
// 	// 设置地板和天花板颜色
// 	tex->floor_color = 0x404040;
// 	tex->ceiling_color = 0x87CEEB;
// 	tex->floor_r = 64;
// 	tex->floor_g = 64;
// 	tex->floor_b = 64;
// 	tex->ceiling_r = 135;
// 	tex->ceiling_g = 206;
// 	tex->ceiling_b = 235;

// }

int    init_texture_defaults(t_texture *tex)
{
    tex->no.img_ptr = NULL;
    tex->so.img_ptr = NULL;
    tex->we.img_ptr = NULL;
    tex->ea.img_ptr = NULL;
    tex->no.data = NULL;
    tex->so.data = NULL;
    tex->we.data = NULL;
    tex->ea.data = NULL;
    tex->no_path = ft_strdup("textures/mur/north.xpm");
	tex->so_path = ft_strdup("textures/mur/south.xpm");
	tex->we_path = ft_strdup("textures/mur/west.xpm");
	tex->ea_path = ft_strdup("textures/mur/east.xpm");

    /*
    // tex->floor_img.img_ptr = NULL;
    // tex->ceiling_img.img_ptr = NULL;
    // tex->floor_img.data = NULL;
    // tex->ceiling_img.data = NULL;
    // tex->floor_path = ft_strdup("textures/floor/floor.xpm");
    // tex->ceiling_path = ft_strdup("textures/sky/sky.xpm");
	// if (!tex->no_path || !tex->so_path || 
	// 	!tex->we_path || !tex->ea_path || 
    //     !tex->floor_path || !tex->ceiling_path)
    */
    if (!tex->no_path || !tex->so_path || 
		!tex->we_path || !tex->ea_path)
    {
		ft_fprintf(2, "Error: Failed to allocate texture paths\n");
		return (0);
	}
	// 临时使用纯色代替纹理
	// 设置地板和天花板颜色
	tex->floor_color = 0x404040;
	tex->ceiling_color = 0x87CEEB;
	tex->floor_r = 64;
	tex->floor_g = 64;
	tex->floor_b = 64;
	tex->ceiling_r = 135;
	tex->ceiling_g = 206;
	tex->ceiling_b = 235;
    return (1);

}

int init_texture_img(void *mlx_ptr, t_img *img, const char *path)
{
    if (!mlx_ptr || !img || !path || *path == '\0')
        return (0);
    img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, (char *)path,
                    &img->width, &img->height);
    if (!img->img_ptr)
        return (0);
    img->data = mlx_get_data_addr(img->img_ptr,
                    &img->bpp, &img->size_line, &img->endian);
    if (!img->data)
    {
        mlx_destroy_image(mlx_ptr, img->img_ptr);
        img->img_ptr = NULL;
        return (0);
    }
    return (1);
}


void    free_textures(t_texture *tex, void *mlx_ptr)
{
    free_img(mlx_ptr, &tex->no);
    free_img(mlx_ptr, &tex->so);
    free_img(mlx_ptr, &tex->we);
    free_img(mlx_ptr, &tex->ea);
    if (tex->no_path)
        free(tex->no_path);
    if (tex->so_path)
        free(tex->so_path);
    if (tex->we_path)
        free(tex->we_path);
    if (tex->ea_path)
        free(tex->ea_path);
    tex->no_path = NULL;
    tex->so_path = NULL;
    tex->we_path = NULL;
    tex->ea_path = NULL;

    // free_img(mlx_ptr, &tex->floor_img);
    // free_img(mlx_ptr, &tex->ceiling_img);
    // if (tex->floor_path)
    //     free(tex->floor_path);
    // if (tex->ceiling_path)
    //     free(tex->ceiling_path);
    // tex->floor_path = NULL;
    // tex->ceiling_path = NULL;
}

static int  check_all_paths_ready(t_texture *t)
{
    if (!t->no_path || !t->so_path)
        return (0);
    if (!t->we_path || !t->ea_path)
        return (0);
    /*
    // if (!t->floor_path || !t->ceiling_path)
    //     return (0);
    */
    return (1);
}

int	init_textures(t_texture *tex, void *mlx_ptr)
{
	if (!check_all_paths_ready(tex))
        return (0);
    // if (!init_texture_img(mlx_ptr, &tex->no, tex->no_path)
    // || !init_texture_img(mlx_ptr, &tex->so, tex->so_path)
    // || !init_texture_img(mlx_ptr, &tex->we, tex->we_path)
    // || !init_texture_img(mlx_ptr, &tex->ea, tex->ea_path)
    // || !init_texture_img(mlx_ptr, &tex->floor_img, tex->floor_path)
    // || !init_texture_img(mlx_ptr, &tex->ceiling_img, tex->ceiling_path))
    if (!init_texture_img(mlx_ptr, &tex->no, tex->no_path)
    || !init_texture_img(mlx_ptr, &tex->so, tex->so_path)
    || !init_texture_img(mlx_ptr, &tex->we, tex->we_path)
    || !init_texture_img(mlx_ptr, &tex->ea, tex->ea_path))
    {
        free_textures(tex, mlx_ptr);
        return (0);
    }
	return (1);
}