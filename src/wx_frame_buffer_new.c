/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_frame_buffer_new.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: name <name@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 10:56:17 by name          #+#    #+#             */
/*   Updated: 2021/03/24 15:47:43 by name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wx_frame_buffer.h"

t_bool	wx_frame_buffer_new(t_frame_buffer *fb, t_u32 image_width,
	t_u32 image_height)
{
	fb->data_size = image_width * image_height * 4;
	fb->data = (t_u8 *)malloc(fb->data_size);
	if (!fb->data)
		return (wx_false);
	wx_buffer_set(fb->data, fb->data_size, 0);
	fb->width = image_width;
	fb->height = image_height;
	return (wx_true);
}
