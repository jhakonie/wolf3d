/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_position_mouse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 13:28:24 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/27 13:29:28 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

t_bool			we_pos_mouse_tool(t_tool *t, t_u32 *draw, t_u32 x, t_u32 y)
{
	if (x >= t->button.start.x && x <= t->button.end.x &&
	y >= t->button.start.y && y <= t->button.end.y)
	{
		t->pre_selected = wx_true;
		*draw = wx_true;
	}
	if (x <= t->button.start.x || x >= t->button.end.x ||
	y <= t->button.start.y || y >= t->button.end.y)
	{
		t->pre_selected = wx_false;
		*draw = wx_true;
		return (wx_false);
	}
	return (wx_true);
}

void			we_pos_mouse_grid(t_map *m, t_u32 *draw, t_u32 x, t_u32 y)
{
	m->ptr.x = x;
	m->ptr.y = y;
	m->ptr_draw = wx_true;
	*draw = wx_true;
}
