/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_save_win_to_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:11:52 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/19 16:13:30 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_save_win_to_map(t_p2 win, t_editor *e)
{
	t_u32	tile_index;
	t_p2	map;

	map = we_from_win_to_map(win, e->map_view);
	if (map.x < WX_MAP_TILES_WIDTH && map.y < WX_MAP_TILES_WIDTH)
	{
		tile_index = (int)map.x + WX_MAP_TILES_WIDTH * (int)(map.y);
		if (e->tools.id == 4)
			e->level.map.tiles[tile_index] = 0;
		else
			e->level.map.tiles[tile_index] = e->tools.id;
	}
}
