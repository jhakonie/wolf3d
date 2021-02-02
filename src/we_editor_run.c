/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_editor_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:50:59 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/02 23:23:33 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL2/SDL.h"
#include "wx_frame_buffer.h"
#include "wx_types.h"
#include "we_editor.h"

static void		zz_draw_map(t_editor *e)
{
	(void)e;
	e->draw = wx_false;
}

static t_bool	zz_events(t_editor *e)
{
	if (SDL_WaitEvent(&e->event) != 0)
	{
		if (e->event.type == SDL_QUIT)
		{
			return (wx_true);
		}
		else if (e->event.type == SDL_KEYDOWN)
		{
			if (e->event.key.keysym.sym == SDLK_ESCAPE)
				return (wx_true);
		}
		else if (e->event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		{
			we_editor_on_resize(e, e->event.window.data1,
								e->event.window.data2);
		}
	}
	return (wx_false);
}

t_bool			we_editor_run(t_editor *e)
{
	int			*texture_data;
	t_s32		texture_pitch;

	while (!e->quit)
	{
		if (e->draw)
		{
			zz_draw_map(e);
			if (SDL_LockTexture(e->texture, WX_NULL, (void **)&texture_data,
								&texture_pitch) < 0)
			{
				e->quit = wx_true;
			}
			wx_buffer_copy(texture_data, e->frame_buffer.data,\
			e->frame_buffer.data_size);
			SDL_UnlockTexture(e->texture);
			if (SDL_RenderCopy(e->renderer, e->texture, WX_NULL, WX_NULL) < 0)
			{
				e->quit = wx_true;
			}
			SDL_RenderPresent(e->renderer);
		}
		e->quit = zz_events(e);
	}
	return (wx_true);
}
