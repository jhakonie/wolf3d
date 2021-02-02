/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_editor_on_resize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 22:51:08 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/02 22:55:02 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_editor_on_resize(t_editor *e, t_s32 width, t_s32 height)
{
	free(e->frame_buffer.data);
	e->frame_buffer.data = 0;
	e->frame_buffer.data_size = width * height * 4;
	if (!(e->frame_buffer.data = (t_u8 *)malloc(e->frame_buffer.data_size)))
	{
		e->quit = wx_true;
	}
	wx_buffer_set(e->frame_buffer.data, e->frame_buffer.data_size, 0);
}
