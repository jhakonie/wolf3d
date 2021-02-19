/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:43:30 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/18 21:59:18 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"

void	wc_draw_pixel(t_frame_buffer *fb, t_f32 x, t_f32 y, t_u32 abgr)
{
	t_u64	i;

	i = 4 * ((t_u32)y * fb->width + (t_u32)x);
	fb->data[i + 0] = (abgr >> 24) & 0xff;
	fb->data[i + 1] = (abgr >> 16) & 0xff;
	fb->data[i + 2] = (abgr >> 8) & 0xff;
	fb->data[i + 3] = (abgr >> 0) & 0xff;
}
