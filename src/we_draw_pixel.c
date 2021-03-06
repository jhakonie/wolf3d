/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:25:21 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/01 12:28:03 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void		we_u32_to_rgba(t_rgba *color, t_u32 color_int)
{
	color->a = (color_int >> 24);
	color->b = (color_int) & 0xFF;
	color->g = (color_int >> 8) & 0xFF;
	color->r = (color_int >> 16) & 0xFF;
}

/*
** 2021-03-01 todo: work out what the conversion from f32 to u32 should look
** like. is there need to + 0.5f?
*/

void		we_draw_pixel(t_p2 point, t_frame_buffer *fb, t_rgba color)
{
	t_u32	x;
	t_u32	y;

	x = point.x;
	y = point.y;
	if (point.x < fb->width && point.y < fb->height)
	{
		fb->data[0 + (x + fb->width * y) * 4] = color.a;
		fb->data[1 + (x + fb->width * y) * 4] = color.b;
		fb->data[2 + (x + fb->width * y) * 4] = color.g;
		fb->data[3 + (x + fb->width * y) * 4] = color.r;
	}
}
