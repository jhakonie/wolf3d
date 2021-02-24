/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 20:44:57 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/24 20:45:41 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void		zz_color_ptr(t_editor *e)
{
	t_p2	top;
	t_p2	low;
	t_rgba	color;

	low.x = e->map.ptr.x - e->map.grid.part.x / 2;
	low.y = e->map.ptr.y - e->map.grid.part.y / 2;
	top.x = e->map.ptr.x + e->map.grid.part.x / 2;
	top.y = e->map.ptr.y + e->map.grid.part.y / 2;
	if (e->tools.id != WE_ID_INIT)
		color = e->tools.tool[e->tools.id].button.color[0];
	else
		return ;
	we_draw_rec_full(low, top, &e->frame_buffer, color);
	e->map.ptr_draw = wx_false;
}

void		we_draw(t_editor *e)
{
	if (e->map.ptr_clear || (e->map.ptr_draw && e->tools.id != WE_ID_INIT))
	{
		wx_buffer_set(e->frame_buffer.data, e->frame_buffer.data_size, 0);
		we_draw_map(e);
		zz_color_ptr(e);
		e->map.ptr_clear = wx_false;
	}
	else
		we_draw_map(e);
	we_draw_toolbar(e);
	we_draw_grid(&e->map.grid, &e->frame_buffer);
	e->draw = wx_false;
}
