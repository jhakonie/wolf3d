/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw_rectangle_outline.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:22:54 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/18 22:20:10 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"

static void	zz_draw_horizontal_line(t_frame_buffer *fb, t_f32 x0, t_f32 x1,
	t_f32 y)
{
	if (y < 0 || y >= fb->height)
	{
		return ;
	}
	x0 = wx_f32_max(x0, 0);
	x1 = wx_f32_min(x1, fb->width);
	while (x0 < x1)
	{
		wc_draw_pixel(fb, x0, y, 0xff666666);
		++x0;
	}
}

static void	zz_draw_vertical_line(t_frame_buffer *fb, t_f32 y0, t_f32 y1,
	t_f32 x)
{
	if (x < 0 || x >= fb->width)
	{
		return ;
	}
	y0 = wx_f32_max(y0, 0);
	y1 = wx_f32_min(y1, fb->height);
	while (y0 < y1)
	{
		wc_draw_pixel(fb, x, y0, 0xff666666);
		++y0;
	}
}

void		wc_draw_rectangle_outline(t_frame_buffer *fb, t_rectangle r)
{
	zz_draw_horizontal_line(fb, r.p0.x, r.p1.x, r.p0.y);
	zz_draw_horizontal_line(fb, r.p0.x, r.p1.x, r.p1.y);
	zz_draw_vertical_line(fb, r.p0.y, r.p1.y, r.p0.x);
	zz_draw_vertical_line(fb, r.p0.y, r.p1.y, r.p1.x);
}
