/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_editor_on_resize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 22:51:08 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/27 21:25:46 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

/*
** SDL_DestrtroyRenderer() destroys related textures.
*/

static void	zz_on_resize(t_editor *e, t_s32 width, t_s32 height)
{
	SDL_DestroyRenderer(e->renderer);
	e->renderer = SDL_CreateRenderer(e->window, -1, 0);
	if (!e->renderer)
		e->quit = wx_true;
	e->texture = SDL_CreateTexture(e->renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, width, height);
	if (!e->texture)
		e->quit = wx_true;
	free(e->frame_buffer.data);
	e->frame_buffer.data = 0;
	e->frame_buffer.data_size = width * height * 4;
	e->frame_buffer.data = (t_u8 *)malloc(e->frame_buffer.data_size);
	if (!e->frame_buffer.data)
	{
		e->quit = wx_true;
	}
	wx_buffer_set(e->frame_buffer.data, e->frame_buffer.data_size, 0);
	e->frame_buffer.width = width;
	e->frame_buffer.height = height;
	we_init_map(&e->map, width, height);
	we_init_tools(&e->tools, width, height);
	e->draw = wx_true;
}

static void	zz_on_expose(t_editor *e)
{
	we_draw_to_window(e);
	e->draw = wx_true;
}

void	we_window_event(t_editor *e, SDL_WindowEvent *w)
{
	if (e->event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		zz_on_resize(e, w->data1, w->data2);
	else if (e->event.window.event == SDL_WINDOWEVENT_EXPOSED)
		zz_on_expose(e);
}
