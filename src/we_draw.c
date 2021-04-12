/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 20:44:57 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/11 00:57:03 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static void	zz_color_ptr(t_editor *e)
{
	t_p2	top;
	t_p2	temp;
	t_p2	low;
	t_u32	color;

	temp = we_from_win_to_map(e->map.ptr, e->map);
	low = we_from_map_to_win(temp, e->map);
	top.x = low.x + e->map.grid.part.x;
	top.y = low.y + e->map.grid.part.y;
	if (e->tools.id != WE_ID_INIT)
		color = e->tools.tool[e->tools.id].button.color[0];
	else
		return ;
	we_draw_rec_full(low, top, &e->frame_buffer, color);
}

void	we_draw(t_editor *e)
{
	if (e->map.draw_3d == wx_false)
	{
		wx_buffer_set(e->frame_buffer.data, e->frame_buffer.data_size, 0);
		we_draw_toolbar(e);
	}
	we_draw_3d(&e->frame_buffer, e->player, e->map);
	if (e->map.draw_3d == wx_false)
		we_draw_grid(&e->map.grid, &e->frame_buffer);
	if (e->map.draw_3d == wx_false && (e->map.ptr_clear || (e->map.ptr_draw)))
	{
		we_draw_map(e);
		we_draw_player(e);
		if (e->map.ptr_draw && !e->map.ptr_clear)
			zz_color_ptr(e);
		e->map.ptr_clear = wx_false;
	}
	else if (e->map.draw_3d == wx_false)
	{
		we_draw_map(e);
		we_draw_player(e);
	}
	e->draw = wx_false;
}
