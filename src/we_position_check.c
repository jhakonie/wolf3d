/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_position_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 00:24:00 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/09 16:02:42 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void			we_position_on_click_tool(t_editor *e, t_u32 x, t_u32 y)
{
	t_u32		i;
	t_u32		state;

	i = 0;
	while (i < 3)
	{
		state = we_pos_on_click_tool(&e->tools.tool[i], &e->draw, x, y);
		if (state == wx_false)
		{
			if (e->tools.id != WE_ID_INIT)
			{
				e->tools.tool[e->tools.id].selected = wx_false;
				e->tools.tool[e->tools.id].pre_selected = wx_false;
			}
			e->tools.id = i;
		}
		if (e->tools.tool[e->tools.id].pre_selected == wx_true)
		{
			e->tools.id = WE_ID_INIT;
			e->map.ptr_clear = wx_true;
		}
		i++;
	}
}

t_bool			we_pos_on_click_tool(t_tool *t, t_u32 *draw, t_u32 x, t_u32 y)
{
	if (t->pre_selected && !t->selected)
	{
		t->selected = wx_true;
		t->pre_selected = wx_false;
		*draw = wx_true;
		return (wx_false);
	}
	else if (t->selected && x >= t->button.start.x &&
	x <= t->button.end.x && y >= t->button.start.y &&
	y <= t->button.end.y)
	{
		t->selected = wx_false;
		t->pre_selected = wx_true;
		*draw = wx_true;
	}
	return (wx_true);
}

void			we_pos_on_click_grid(t_map *m, t_u32 *draw, t_u32 x, t_u32 y)
{
	m->new_block.x = x;
	m->new_block.y = y;
	m->new_block_draw = wx_true;
	*draw = wx_true;
}

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
