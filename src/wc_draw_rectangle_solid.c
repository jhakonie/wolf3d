/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw_rectangle_solid.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 23:41:37 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/18 21:12:17 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"

void	wc_draw_rectangle_solid(t_frame_buffer *fb, t_rectangle r)
{
	t_u32	x;
	t_u32	y;

	r.p0.x = wx_f32_max(r.p0.x, 0.0f);
	r.p0.y = wx_f32_max(r.p0.y, 0.0f);
	r.p1.x = wx_f32_min(r.p1.x, fb->width);
	r.p1.y = wx_f32_min(r.p1.y, fb->height);
	y = r.p0.y;
	while (y < r.p1.y)
	{
		x = r.p0.x;
		while (x < r.p1.x)
		{
			wc_draw_pixel(fb, x, y, 0xff00aaff);
			++x;
		}
		++y;
	}
}
