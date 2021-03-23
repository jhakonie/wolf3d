/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:46:35 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/23 13:09:32 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void		we_draw_player(t_editor *e)
{
	t_p2	start;
	t_p2	end;
	t_p2	delta;
	t_f32	angle;

	start.x = (e->player.position.x / WE_BLOCK_W) * e->map.grid.part.x +
				e->tools.end.x - 3;
	start.y = e->player.position.y / WE_BLOCK_W * e->map.grid.part.y - 3;
	end.x = start.x + 3;
	end.y = start.y + 3;
	we_draw_rec_full(start, end, &e->frame_buffer, 0xff00FF);
	start.x = start.x;
	start.y = start.y;
	angle = e->player.direction_d;
	delta.x = (cos(angle * WE_TO_RAD) * 1000);
	delta.y = -(sin(angle * WE_TO_RAD) * 1000);
	end.x = (start.x + delta.x);
	end.y = (start.y + delta.y);
	we_draw_line(start, end, &e->frame_buffer, 0xff00FF);
}
