/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:25:21 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/27 13:25:14 by jhakonie         ###   ########.fr       */
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

void		we_draw_pixel(t_p2 point, t_frame_buffer *fb, t_rgba color)
{
	if (point.x < fb->width && point.y < fb->height)
	{
		fb->data[0 + (point.x + fb->width * point.y) * 4] = color.a;
		fb->data[1 + (point.x + fb->width * point.y) * 4] = color.b;
		fb->data[2 + (point.x + fb->width * point.y) * 4] = color.g;
		fb->data[3 + (point.x + fb->width * point.y) * 4] = color.r;
	}
}
