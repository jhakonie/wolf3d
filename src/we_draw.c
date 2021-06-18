/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 20:44:57 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/17 01:22:38 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static void	zz_color_ptr(t_editor *e)
{
	t_p2	top;
	t_p2	temp;
	t_p2	low;

	temp = we_from_win_to_map(e->map_view.ptr, e->map_view);
	low = we_from_map_to_win(temp, e->map_view);
	top.x = low.x + e->map_view.grid.part.x;
	top.y = low.y + e->map_view.grid.part.y;
	we_draw_rec_texture(low, top, &e->frame_buffer,
		&e->tools.tool[e->tools.id].button.icon);
	if (e->tools.id == 4)
		we_draw_rec_frame(low, top, &e->frame_buffer, 0xffffff);
}

static void	zz_draw_2d(t_editor *e)
{
	wx_buffer_set(e->frame_buffer.data, e->frame_buffer.data_size, 0);
	we_draw_map(e);
	we_draw_player(e);
	if (e->map_view.ptr_clear || (e->map_view.ptr_draw))
	{
		if (e->map_view.ptr_draw && !e->map_view.ptr_clear)
			zz_color_ptr(e);
		e->map_view.ptr_clear = wx_false;
	}
	we_draw_toolbar(e);
	we_draw_grid(&e->map_view.grid, &e->frame_buffer);
}

void	we_draw(t_editor *e)
{
	if (!e->map_view.draw_3d)
		zz_draw_2d(e);
	else
		we_draw_3d(&e->frame_buffer, e->player, &e->level.map);
	e->draw = wx_false;
}
