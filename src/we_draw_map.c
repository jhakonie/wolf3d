/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:52:54 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/15 22:30:29 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"
#include "wc_draw.h"

void	we_draw_map(t_editor *e)
{
	t_u32	i;
	t_p2	start;
	t_p2	end;

	i = 0;
	while (i < e->map.block_count)
	{
		if (e->map.tiles[i].id != WE_ID_INIT)
		{
			start = we_from_map_to_win(e->map.tiles[i].block, e->map);
			end.x = start.x + e->map.grid.part.x;
			end.y = start.y + e->map.grid.part.y;
			we_draw_rec_full(start, end, &e->frame_buffer,
				e->tools.tool[e->map.tiles[i].id].button.color[0]);
		}
		i++;
	}
}
