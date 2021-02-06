/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_editor_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:50:59 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/04 00:08:02 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static void		zz_mouse_move(t_editor *e, t_s32 x, t_s32 y)
{
	if (x >= e->tool.button.start.x && x <= e->tool.button.end.x &&
	y >= e->tool.button.start.y && y <= e->tool.button.end.y)
	{
		e->tool.pre_selected = wx_true;
		e->draw = wx_true;
	}
	if (x <= e->tool.button.start.x || x >= e->tool.button.end.x ||
	y <= e->tool.button.start.y || y >= e->tool.button.end.y)
	{
		e->tool.pre_selected = wx_false;
		e->draw = wx_true;
	}
}

static void		zz_mouse_button(t_editor *e, t_u32 x, t_u32 y)
{
	if (e->event.button.button == SDL_BUTTON_LEFT)
	{
		if (e->tool.pre_selected && !e->tool.selected)
		{
			e->tool.selected = wx_true;
			e->tool.pre_selected = wx_false;
			e->draw = wx_true;
		}
		else if (e->tool.selected && x >= e->tool.button.start.x &&
		x <= e->tool.button.end.x && y >= e->tool.button.start.y &&
		y <= e->tool.button.end.y)
		{
			e->tool.selected = wx_false;
			e->tool.pre_selected = wx_true;
			e->draw = wx_true;
		}
	}
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
			we_editor_on_resize(e, e->event.window.data1,
								e->event.window.data2);
		else if (e->event.type == SDL_MOUSEMOTION)
			zz_mouse_move(e, e->event.motion.x, e->event.motion.y);
		else if (e->event.type == SDL_MOUSEBUTTONDOWN)
			zz_mouse_button(e, e->event.button.x, e->event.button.y);
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
			we_draw_button(e);
			if (SDL_LockTexture(e->texture, WX_NULL, (void **)&texture_data,
								&texture_pitch) < 0)
			{
				e->quit = wx_true;
			}
			wx_buffer_copy(texture_data, e->frame_buffer.data,
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
