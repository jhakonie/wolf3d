/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 20:26:29 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 21:24:34 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_draw_grid(t_grid *g, t_frame_buffer *fb)
{
	t_p2	start;
	t_p2	end;
	t_u32	i;

	i = 1;
	start.y = g->part.y;
	end.x = fb->width - 1;
	end.y = g->part.y;
	while (i < g->divide)
	{
		start.x = g->start.x;
		while (start.x < end.x)
		{
			we_draw_pixel(start, fb, g->color[0]);
			start.x += g->part.x;
		}
		start.y += g->part.y;
		end.y += g->part.y;
		i++;
	}
}
