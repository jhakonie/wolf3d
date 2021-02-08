/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_editor_on_resize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 22:51:08 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/08 13:29:48 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

/*
** SDL_DestrtroyRenderer() destroys related textures.
*/

void	we_editor_on_resize(t_editor *e, t_s32 width, t_s32 height)
{
	SDL_DestroyRenderer(e->renderer);
	if (!(e->renderer = SDL_CreateRenderer(e->window, -1, 0)))
		e->quit = wx_true;
	if (!(e->texture = SDL_CreateTexture(e->renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING, width, height)))
		e->quit = wx_true;
	free(e->frame_buffer.data);
	e->frame_buffer.data = 0;
	e->frame_buffer.data_size = width * height * 4;
	if (!(e->frame_buffer.data = (t_u8 *)malloc(e->frame_buffer.data_size)))
	{
		e->quit = wx_true;
	}
	wx_buffer_set(e->frame_buffer.data, e->frame_buffer.data_size, 0);
	e->frame_buffer.width = width;
	e->frame_buffer.height = height;
}
