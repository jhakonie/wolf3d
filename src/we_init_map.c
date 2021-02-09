/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 20:34:33 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/09 15:43:55 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_init_map(t_map *m, t_u32 win_w, t_u32 win_h)
{
	m->grid.divide = WE_GRID_DIVIDE;
	m->grid.start.x = win_w / 8;
	m->grid.start.y = 0;
	m->grid.end.x = win_w - 1;
	m->grid.end.y = win_h - 1;
	m->grid.part.x = (win_w - m->grid.start.x) / m->grid.divide;
	m->grid.part.y = win_h / m->grid.divide;
	m->block_count = WE_GRID_DIVIDE * WE_GRID_DIVIDE;
	m->old_block_draw = wx_false;
	m->new_block_draw = wx_false;
	m->new_block.x = 0;
	m->new_block.y = 0;
	m->old_block.x = 0;
	m->old_block.y = 0;
	m->ptr.x = 0;
	m->ptr.y = 0;
	m->ptr_draw = wx_false;
	m->ptr_clear = wx_false;
	we_u32_to_rgba(&m->grid.color[0], 0xFFFFFF);
	we_u32_to_rgba(&m->grid.color[1], 0x0000FF);
}
