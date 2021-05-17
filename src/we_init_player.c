/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_init_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 21:24:00 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/16 21:03:15 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	zz_player_pos_set(t_map *m, t_player *p, t_u32 i)
{
	m->tiles[i].id = 3;
	m->player_pos_tiles = m->tiles[i].block;
	m->player_pos_tiles_old = m->tiles[i].block;
	m->player_pos_old_id = 0;
	p->position.x = m->tiles[i].block.x * WE_BLOCK_W + WE_BLOCK_W * 0.5f;
	p->position.y = m->tiles[i].block.y * WE_BLOCK_W + WE_BLOCK_W * 0.5f;
}

void	zz_player_pos(t_map *m, t_player *p)
{
	t_u32	i;

	i = 0;
	while (i < p->w_block_count)
	{
		if (m->tiles[i].id == 3)
		{
			zz_player_pos_set(m, p, i);
			break ;
		}
		i++;
	}
	if (i == p->w_block_count)
		zz_player_pos_set(m, p, 0);
}

void	we_init_player(t_player *p, t_map *m, t_u32 screen_width)
{
	p->direction_d = 45;
	p->height = 0.5f;
	p->fov_d = 60;
	p->dist_to_screen = 0.5f * screen_width
		/ tanf(wx_to_radians(0.5f * p->fov_d));
	p->w_start.x = 0;
	p->w_start.y = 0;
	p->w_end.x = WE_BLOCK_W * WE_GRID_DIVIDE;
	p->w_end.y = WE_BLOCK_W * WE_GRID_DIVIDE;
	p->w_block_count = WE_GRID_DIVIDE * WE_GRID_DIVIDE;
	p->w_step = WE_BLOCK_W * 0.25f;
	p->run = wx_false;
	p->wall_collision = wx_true;
	zz_player_pos(m, p);
}
