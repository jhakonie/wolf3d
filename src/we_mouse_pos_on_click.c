/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_mouse_pos_on_click.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 00:24:00 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/23 13:35:32 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

t_bool			zz_update_tool_state(t_tool *t, t_u32 *draw, t_u32 x, t_u32 y)
{
	if (t->pre_selected && !t->selected)
	{
		t->selected = wx_true;
		t->pre_selected = wx_false;
		*draw = wx_true;
		return (wx_true);
	}
	else if (t->selected && x >= t->button.start.x &&
	x <= t->button.end.x && y >= t->button.start.y &&
	y <= t->button.end.y)
	{
		t->selected = wx_false;
		t->pre_selected = wx_true;
		*draw = wx_true;
	}
	return (wx_false);
}

void			we_pos_on_click_tool(t_editor *e, t_u32 x, t_u32 y)
{
	t_u32		i;
	t_u32		tool_is_selected;

	i = 1;
	while (i < WE_TOOL_COUNT)
	{
		if ((tool_is_selected = zz_update_tool_state(&e->tools.tool[i],
			&e->draw, x, y) && e->tools.id != i))
		{
			e->tools.tool[e->tools.id].selected = wx_false;
			e->tools.tool[e->tools.id].pre_selected = wx_false;
			e->tools.id = i;
		}
		else if (!tool_is_selected && e->tools.tool[i].pre_selected)
			e->tools.id = WE_ID_INIT;
		if (e->tools.id == WE_TOOL_COUNT - 1)
			we_save_map_to_file(e);
		i++;
	}
}

static t_bool	zz_player_position(t_p2 win, t_editor *e)
{
	t_p2	player_pos;
	t_u32	index;
	t_u32	id;

	player_pos = we_from_win_to_map(win, e);
	index = player_pos.x + player_pos.y * WE_GRID_DIVIDE;
	if (e->map.chart[index].id == 0 || e->map.chart[index].id == 2)
	{
		e->map.player_pos_chart = player_pos;
		id = e->map.player_pos_old_id;
		e->map.player_pos_old_id = e->map.chart[index].id;
		e->player.position.x = e->map.player_pos_chart.x * WE_BLOCK_W +
			0.5 * WE_BLOCK_W;
		e->player.position.y = e->map.player_pos_chart.y * WE_BLOCK_W +
			0.5 * WE_BLOCK_W;
		index = e->map.player_pos_chart_old.x +
			e->map.player_pos_chart_old.y * WE_GRID_DIVIDE;
		e->map.chart[index].id = id;
		e->map.player_pos_chart_old = e->map.player_pos_chart;
		e->map.ptr_clear = wx_true;
		return (wx_true);
	}
	e->draw = wx_true;
	return (wx_false);
}

/*
** todo: add "nothing can be placed on player location"
*/

void			we_pos_on_click_grid(t_editor *e, t_u32 x, t_u32 y)
{
	t_p2	win;

	win.x = x;
	win.y = y;
	if ((e->tools.id == 1 || e->tools.id == 4 || e->tools.id == 2) &&
			e->tools.tool[e->tools.id].selected)
		e->map.ptr_hold = wx_true;
	if (e->tools.id == 3)
	{
		if (!zz_player_position(win, e))
			return ;
	}
	if (e->tools.id != WE_ID_INIT && e->tools.id != WE_TOOL_COUNT - 1)
		we_save_win_to_map(win, e);
	e->draw = wx_true;
}
