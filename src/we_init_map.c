/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 20:34:33 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/15 17:37:12 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_init_map(t_map *m, t_u32 win_w, t_u32 win_h)
{
	m->grid.divide = WE_GRID_DIVIDE;
	m->grid.start.x = (win_w - 1) / 8;
	m->grid.start.y = 0;
	m->grid.end.x = win_w - 1;
	m->grid.end.y = win_h - 1;
	m->grid.part.x = (m->grid.end.x - m->grid.start.x) / m->grid.divide;
	m->grid.part.y = m->grid.end.y / m->grid.divide;
	m->block_count = WE_GRID_DIVIDE * WE_GRID_DIVIDE;
	m->ptr_draw = wx_false;
	m->ptr_clear = wx_false;
	m->ptr.x = 0;
	m->ptr.y = 0;
	m->ptr_hold = wx_false;
	m->draw_rays = wx_false;
	m->grid.color[0] = 0xAAB0AF;
	m->grid.color[1] = 0x0000FF;
}
