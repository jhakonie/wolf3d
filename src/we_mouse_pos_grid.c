/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_mouse_pos_grid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 00:24:00 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/30 13:52:24 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static t_bool	zz_player_position(t_p2 win, t_editor *e)
{
	t_p2	player_pos;
	t_u32	index;
	t_u32	id;

	player_pos = we_from_win_to_map(win, e->map_view);
	index = player_pos.x + player_pos.y * WX_MAP_TILES_WIDTH;
	if (e->level.map.tiles[index] == 0 || e->level.map.tiles[index] == 2)
	{
		e->map_view.player_pos_tiles = player_pos;
		id = e->map_view.player_pos_old_id;
		e->map_view.player_pos_old_id = e->level.map.tiles[index];
		e->player.position.x = e->map_view.player_pos_tiles.x * WX_TILE_WIDTH
			+ 0.5 * WX_TILE_WIDTH;
		e->player.position.y = e->map_view.player_pos_tiles.y * WX_TILE_WIDTH
			+ 0.5 * WX_TILE_WIDTH;
		index = e->map_view.player_pos_tiles_old.x
			+ e->map_view.player_pos_tiles_old.y * WX_MAP_TILES_WIDTH;
		e->level.map.tiles[index] = id;
		e->map_view.player_pos_tiles_old = e->map_view.player_pos_tiles;
		e->map_view.ptr_clear = wx_true;
		return (wx_true);
	}
	e->draw = wx_true;
	return (wx_false);
}

void	we_mouse_pos_grid_on_click(t_editor *e, t_u32 x, t_u32 y)
{
	t_p2	win;

	win.x = x;
	win.y = y;
	if ((e->tools.id == 1 || e->tools.id == 4 || e->tools.id == 2)
		&& e->tools.tool[e->tools.id].selected)
		e->map_view.ptr_hold = wx_true;
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
	e->map_view.ptr.x = x;
	e->map_view.ptr.y = y;
	if (e->map_view.ptr_hold)
	{
		we_save_win_to_map(e->map_view.ptr, e);
	}
	if (e->tools.id != WE_TOOL_COUNT - 1)
		e->map_view.ptr_draw = wx_true;
	e->draw = wx_true;
}
