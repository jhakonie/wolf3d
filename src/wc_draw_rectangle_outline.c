/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw_rectangle_outline.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:22:54 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 14:47:30 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"
#include "wx_math.h"

static void	zz_draw_horizontal_line(t_frame_buffer *fb, t_rectangle const *r,
	t_f32 y, t_u32 abgr)
{
	t_f32	x0;
	t_f32	x1;

	x0 = r->p0.x;
	x1 = r->p1.x;
	while (x0 < x1)
	{
		wx_frame_buffer_set(fb, x0, y, abgr);
		++x0;
	}
}

static void	zz_draw_vertical_line(t_frame_buffer *fb, t_rectangle const *r,
	t_f32 x, t_u32 abgr)
{
	t_f32	y0;
	t_f32	y1;

	y0 = r->p0.y;
	y1 = r->p1.y;
	while (y0 < y1)
	{
		wx_frame_buffer_set(fb, x, y0, abgr);
		++y0;
	}
}

void	wc_draw_rectangle_outline(t_frame_buffer *fb, t_p3 p, t_f32 width,
	t_u32 abgr)
{
	t_rectangle	r;
	t_f32		w2;

	w2 = 0.5 * width;
	r.p0.x = wx_f32_max(p.x - w2, 0.0f);
	r.p0.y = wx_f32_max(p.y - w2, 0.0f);
	r.p1.x = wx_f32_min(p.x + w2, fb->width);
	r.p1.y = wx_f32_min(p.y + w2, fb->height);
	zz_draw_horizontal_line(fb, &r, r.p0.y, abgr);
	zz_draw_horizontal_line(fb, &r, r.p1.y, abgr);
	zz_draw_vertical_line(fb, &r, r.p0.x, abgr);
	zz_draw_vertical_line(fb, &r, r.p1.x, abgr);
	(void)abgr;
}
