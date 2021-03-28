/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_init_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 21:24:00 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/24 15:27:28 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	zz_player_pos(t_map *m, t_player *p, t_u32 i)
{
	m->chart[i].id = 3;
	m->player_pos_chart = m->chart[i].block;
	m->player_pos_chart_old = m->chart[i].block;
	m->player_pos_old_id = 0;
	p->position.x = m->chart[i].block.x * WE_BLOCK_W + WE_BLOCK_W / 2;
	p->position.y = m->chart[i].block.y * WE_BLOCK_W + WE_BLOCK_W / 2;
}

void	we_init_player(t_player *p, t_map *m)
{
	t_u32	i;

	i = 0;
	p->direction_d = 45;
	p->w_start.x = 0;
	p->w_start.y = 0;
	p->w_end.x = WE_BLOCK_W * WE_GRID_DIVIDE;
	p->w_end.y = WE_BLOCK_W * WE_GRID_DIVIDE;
	p->w_block_count = WE_GRID_DIVIDE * WE_GRID_DIVIDE;
	p->w_step = WE_BLOCK_W * 0.25;
	p->fov_d = 60;
	while (i < p->w_block_count)
	{
		if (m->chart[i].id == 3)
		{
			zz_player_pos(m, p, i);
			break ;
		}
		i++;
	}
	if (i == p->w_block_count)
		zz_player_pos(m, p, 0);
}
