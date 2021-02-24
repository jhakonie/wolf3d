/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 20:26:29 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/18 22:27:23 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void		zz_draw_vertical(t_grid *g, t_frame_buffer *fb)
{
	t_p2	start;
	t_p2	end;
	t_u32	i;

	i = 0;
	start.x = g->start.x + g->part.x;
	start.y = 0;
	end.x = g->start.x + g->part.x;
	end.y = fb->height - 1;
	while (i < g->divide)
	{
		we_draw_line(start, end, fb, g->color[0]);
		start.x += g->part.x;
		end.x += g->part.x;
		i++;
	}
}

void		zz_draw_horisontal(t_grid *g, t_frame_buffer *fb)
{
	t_p2	start;
	t_p2	end;
	t_u32	i;

	i = 1;
	start.x = g->start.x;
	start.y = g->part.y;
	end.x = fb->width - 1;
	end.y = g->part.y;
	while (i < g->divide)
	{
		we_draw_line(start, end, fb, g->color[0]);
		start.y += g->part.y;
		end.y += g->part.y;
		i++;
	}
}

void		we_draw_grid(t_grid *g, t_frame_buffer *fb)
{
	zz_draw_horisontal(g, fb);
	zz_draw_vertical(g, fb);
}
