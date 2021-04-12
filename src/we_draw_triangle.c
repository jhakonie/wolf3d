/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_triangle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 23:57:29 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/06 15:49:03 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

static void	zz_draw_vertical_line(t_p2 start, t_p2 end, t_frame_buffer *fb,
	t_u32 color)
{
	t_p2	draw_start;
	t_p2	draw_end;

	draw_start.x = start.x;
	draw_end.x = start.x;
	if (start.y < end.y)
	{
		draw_start.y = start.y;
		draw_end.y = end.y;
	}
	else
	{
		draw_start.y = end.y;
		draw_end.y = start.y;
	}
	while (draw_start.y < draw_end.y)
	{
		we_draw_pixel(draw_start, fb, color);
		draw_start.y++;
	}
}

void	we_draw_triangle(t_u32 color, t_triangle *t, t_frame_buffer *fb)
{
	t_p2	draw_start;
	t_p2	draw_end;

	t->color = color;
	draw_start.x = t->points[we_min].x;
	draw_end.x = t->points[we_min].x;
	while (draw_start.x < t->points[we_mid].x)
	{
		draw_start.y = draw_start.x * t->min_max.k + t->min_max.b;
		draw_end.y = draw_end.x * t->min_mid.k + t->min_mid.b;
		zz_draw_vertical_line(draw_start, draw_end, fb, color);
		draw_start.x++;
		draw_end.x++;
	}
	while (draw_start.x <= t->points[we_max].x)
	{
		draw_start.y = draw_start.x * t->min_max.k + t->min_max.b;
		draw_end.y = draw_end.x * t->mid_max.k + t->mid_max.b;
		zz_draw_vertical_line(draw_start, draw_end, fb, color);
		draw_start.x++;
		draw_end.x++;
	}
}
