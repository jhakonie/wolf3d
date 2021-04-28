/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw_rectangle_solid.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 23:41:37 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/06 14:49:43 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"
#include "wx_math.h"

void	wc_draw_rectangle_solid(t_frame_buffer *fb, t_p3 p, t_f32 width,
	t_u32 abgr)
{
	t_rectangle	r;
	t_f32		w2;
	t_u32		x;
	t_u32		y;

	w2 = 0.5 * width;
	r.p0.x = wx_f32_max(p.x - w2, 0.0f);
	r.p0.y = wx_f32_max(p.y - w2, 0.0f);
	r.p1.x = wx_f32_min(p.x + w2, fb->width);
	r.p1.y = wx_f32_min(p.y + w2, fb->height);
	y = r.p0.y;
	while (y < r.p1.y)
	{
		x = r.p0.x;
		while (x < r.p1.x)
		{
			wx_frame_buffer_set(fb, x, y, abgr);
			++x;
		}
		++y;
	}
}
