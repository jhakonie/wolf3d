/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_window_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 22:51:08 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/16 20:00:47 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

/*
** SDL_DestrtroyRenderer() destroys related textures.
*/

static void	zz_on_resize(t_editor *e, t_s32 width, t_s32 height)
{
	t_bool	draw_3d;

	draw_3d = e->map.draw_3d;
	SDL_DestroyRenderer(e->renderer);
	e->renderer = SDL_CreateRenderer(e->window, -1, 0);
	if (!e->renderer)
		e->quit = wx_true;
	e->texture = SDL_CreateTexture(e->renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, width, height);
	if (!e->texture)
		e->quit = wx_true;
	free(e->frame_buffer.data);
	if (!wx_frame_buffer_new(&e->frame_buffer, width, height))
		e->quit = wx_true;
	we_init_map(&e->map, width, height);
	we_init_tools(&e->tools, width, height);
	e->player.dist_to_screen = 0.5f * e->frame_buffer.width
		/ tanf(wx_to_radians(0.5f * e->player.fov_d));
	e->draw = wx_true;
	e->map.draw_3d = draw_3d;
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
