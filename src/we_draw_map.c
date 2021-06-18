/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:52:54 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/17 01:20:16 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_draw_map(t_editor *e)
{
	t_u32	i;
	t_p2	start;
	t_p2	end;

	i = 0;
	while (i < e->map_view.tile_count)
	{
		if (e->level.map.tiles[i].id != WE_ID_INIT)
		{
			start = we_from_map_to_win(e->level.map.tiles[i].tile, e->map_view);
			end.x = start.x + e->map_view.grid.part.x;
			end.y = start.y + e->map_view.grid.part.y;
			we_draw_rec_texture(start, end, &e->frame_buffer,
				&e->tools.tool[e->level.map.tiles[i].id].button.icon);
		}
		i++;
	}
}
