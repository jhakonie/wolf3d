/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_window_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 22:51:08 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/17 01:20:16 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

/*
** SDL_DestrtroyRenderer() destroys related textures.
*/

static void	zz_on_resize(t_editor *e, t_s32 width, t_s32 height)
{
	t_u32	tool_id;
	t_bool	draw_rays;

	draw_rays = e->map_view.draw_rays;
	tool_id = e->tools.id;
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
	we_init_map(&e->map_view, width, height);
	we_init_toolbar(&e->tools, width, height);
	e->tools.id = tool_id;
	e->tools.tool[tool_id].selected = wx_true;
	e->map_view.draw_rays = draw_rays;
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
