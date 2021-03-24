/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:25:21 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/24 15:09:25 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_draw_pixel(t_p2 point, t_frame_buffer *fb, t_u32 color)
{
	t_u32	i;

	i = ((int)point.x + fb->width * (int)point.y) * 4;
	if (point.x < fb->width && point.y < fb->height && point.x >= 0
		&& point.y >= 0)
	{
		fb->data[0 + i] = (color >> 24);
		fb->data[1 + i] = (color) & 0xFF;
		fb->data[2 + i] = (color >> 8) & 0xFF;
		fb->data[3 + i] = (color >> 16) & 0xFF;
	}
}
