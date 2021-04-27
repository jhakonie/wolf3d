/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_mouse_pos_grid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 00:24:00 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/27 21:49:58 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static t_bool	zz_player_position(t_p2 win, t_editor *e)
{
	t_p2	player_pos;
	t_u32	index;
	t_u32	id;

	player_pos = we_from_win_to_map(win, e->map);
	index = player_pos.x + player_pos.y * WE_GRID_DIVIDE;
	if (e->map.chart[index].id == 0 || e->map.chart[index].id == 2)
	{
		e->map.player_pos_chart = player_pos;
		id = e->map.player_pos_old_id;
		e->map.player_pos_old_id = e->map.chart[index].id;
		e->player.position.x = e->map.player_pos_chart.x * WE_BLOCK_W
			+ 0.5 * WE_BLOCK_W;
		e->player.position.y = e->map.player_pos_chart.y * WE_BLOCK_W
			+ 0.5 * WE_BLOCK_W;
		index = e->map.player_pos_chart_old.x
			+ e->map.player_pos_chart_old.y * WE_GRID_DIVIDE;
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

void	we_mouse_pos_grid_on_click(t_editor *e, t_u32 x, t_u32 y)
{
	t_p2	win;

	win.x = x;
	win.y = y;
	if ((e->tools.id == 1 || e->tools.id == 4 || e->tools.id == 2)
		&& e->tools.tool[e->tools.id].selected)
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

void	we_mouse_pos_grid(t_editor *e, t_u32 x, t_u32 y)
{
	e->map.ptr.x = x;
	e->map.ptr.y = y;
	if (e->map.ptr_hold)
	{
		we_save_win_to_map(e->map.ptr, e);
	}
	if (e->tools.id != WE_TOOL_COUNT - 1)
		e->map.ptr_draw = wx_true;
	e->draw = wx_true;
}
