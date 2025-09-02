/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclee <niclee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:08:42 by niclee            #+#    #+#             */
/*   Updated: 2025/09/02 16:13:17 by niclee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	init_parser(t_parse *p)
{
	p->raw_lines = NULL;
	p->raw_count = 0;
	p->map_started = 0;
	p->fd = -1;
	p->got_no = 0;
	p->got_so = 0;
	p->got_we = 0;
	p->got_ea = 0;
	p->got_f = 0;
	p->got_c = 0;
	p->filepath = NULL;
	p->textures = malloc(sizeof(t_texture));
}

static void	init_parser_texture(t_parse *p)
{
	if (p->textures)
	{
		p->textures->no_path = NULL;
		p->textures->so_path = NULL;
		p->textures->we_path = NULL;
		p->textures->ea_path = NULL;
		p->textures->floor_color = 0;
		p->textures->ceiling_color = 0;
		p->textures->floor_r = 0;
		p->textures->floor_g = 0;
		p->textures->floor_b = 0;
		p->textures->ceiling_r = 0;
		p->textures->ceiling_g = 0;
		p->textures->ceiling_b = 0;
	}
}

void	init_all_parser(t_parse *p)
{
	init_parser(p);
	init_parser_texture(p);
}
