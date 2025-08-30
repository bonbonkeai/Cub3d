#include "../../cub3d.h"

// 9. 选择纹理
void select_wall_texture(t_game *game)
{
    if (game->ray.side == 0 && game->ray.ray_dir_x > 0)
        game->wall_params.tex = &game->textures.we;
    else if (game->ray.side == 0 && game->ray.ray_dir_x < 0)
        game->wall_params.tex = &game->textures.ea;
    else if (game->ray.side == 1 && game->ray.ray_dir_y > 0)
        game->wall_params.tex = &game->textures.no;
    else
        game->wall_params.tex = &game->textures.so;
}

// 10. 计算墙面命中点
void calculate_wall_hit(t_game *game)
{
    if (game->ray.side == 0)
        game->temp_wall_x = game->player.y + game->temp_perp_dist * game->ray.ray_dir_y;
    else
        game->temp_wall_x = game->player.x + game->temp_perp_dist * game->ray.ray_dir_x;
    game->temp_wall_x -= floor(game->temp_wall_x);
}

// 11. 计算纹理X坐标
void calculate_tex_x(t_game *game)
{
    int should_flip;
    
    game->wall_params.tex_x = (int)(game->temp_wall_x * (double)game->wall_params.tex->width);
    should_flip = ((game->ray.side == 0 && game->ray.ray_dir_x > 0) || 
                   (game->ray.side == 1 && game->ray.ray_dir_y < 0));
    if (should_flip)
        game->wall_params.tex_x = game->wall_params.tex->width - game->wall_params.tex_x - 1;
    if (game->wall_params.tex_x < 0)
        game->wall_params.tex_x = 0;
    else if (game->wall_params.tex_x >= game->wall_params.tex->width)
        game->wall_params.tex_x = game->wall_params.tex->width - 1;
}

// 12. 计算纹理步长
void calculate_texture_step(t_game *game)
{
    game->wall_params.step = 1.0 * game->wall_params.tex->height / game->draw.line_height;
    game->wall_params.tex_pos = (game->draw.draw_start - game->win_height / 2 
        + game->draw.line_height / 2) * game->wall_params.step;
}
