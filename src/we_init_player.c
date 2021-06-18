/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_init_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 21:24:00 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/19 00:34:07 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	zz_player_pos_set(t_map_view *m, t_map *map, t_player *p, t_u32 i)
{
	map->tiles[i].id = 3;
	m->player_pos_tiles = map->tiles[i].tile;
	m->player_pos_tiles_old = map->tiles[i].tile;
	m->player_pos_old_id = 0;
	p->position.x = map->tiles[i].tile.x * WX_TILE_WIDTH + WX_TILE_WIDTH * 0.5f;
	p->position.y = map->tiles[i].tile.y * WX_TILE_WIDTH + WX_TILE_WIDTH * 0.5f;
}

void	zz_player_pos(t_map_view *m, t_map *map, t_player *p)
{
	t_u32	i;

	i = 0;
	while (i < p->w_tile_count)
	{
		if (map->tiles[i].id == 3)
		{
			zz_player_pos_set(m, map, p, i);
			break ;
		}
		i++;
	}
	if (i == p->w_tile_count)
		zz_player_pos_set(m, map, p, WX_MAP_SIZE * 0.5f);
}

/*
*todo: check step
*/

void	we_init_player(t_player *p, t_map *map, t_map_view *m,
	t_u32 screen_width)
{
	p->direction_d = 90;
	p->height = 0.5f;
	p->fov_d = 60;
	p->dist_to_screen_w = 0.5f * screen_width
		/ tanf(wx_to_radians(0.5f * p->fov_d));
	wx_buffer_set(&p->move, sizeof(p->move), 0);
	p->w_tile_count = WX_MAP_TILES_WIDTH * WX_MAP_TILES_WIDTH;
	p->w_step = 30;
	p->run = wx_false;
	p->wall_collision = wx_true;
	zz_player_pos(m, map, p);
}
