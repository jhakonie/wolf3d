/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:25:21 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/29 20:31:48 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_draw_pixel(t_p2 point, t_frame_buffer *fb, t_u32 color)
{
	t_u64	i;

	i = 4 * ((t_u32)point.y * fb->width + (t_u32)point.x);
	fb->data[i + 0] = (color >> 24) & 0xff;
	fb->data[i + 3] = (color >> 16) & 0xff;
	fb->data[i + 2] = (color >> 8) & 0xff;
	fb->data[i + 1] = (color >> 0) & 0xff;
}
