/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:52:54 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/19 17:16:33 by jhakonie         ###   ########.fr       */
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
		if (e->level.map.tiles[i] != WE_ID_INIT)
		{
			start = we_from_map_to_win((t_p2){i % e->level.map.width,
					i / e->level.map.width}, e->map_view);
			end.x = start.x + e->map_view.grid.part.x;
			end.y = start.y + e->map_view.grid.part.y;
			we_draw_rec_texture(start, end, &e->frame_buffer,
				&e->tools.tool[e->level.map.tiles[i]].button.icon);
		}
		i++;
	}
}
