/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_editor_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:50:59 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/16 00:24:05 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static void		zz_mouse_event_move(t_editor *e, t_u32 x, t_u32 y)
{
	t_u32		i;

	i = 1;
	if (x < e->map.grid.start.x)
	{
		e->map.ptr_draw = wx_false;
		e->map.ptr_clear = wx_true;
		while (i < WE_TOOL_COUNT)
		{
			we_pos_mouse_tool(&e->tools.tool[i], &e->draw, x, y);
			i++;
		}
	}
	else
		we_pos_mouse_grid(e, x, y);
}

static void		zz_mouse_event_click(t_editor *e, t_u32 x, t_u32 y)
{
	if (e->event.button.button == SDL_BUTTON_LEFT)
	{
		if (x < e->map.grid.start.x)
			we_pos_on_click_tool(e, x, y);
		else if (e->tools.id != WE_ID_INIT)
			we_pos_on_click_grid(e, x, y);
	}
}

/*
**todo: add expose event
*/

static t_bool	zz_wait_event(t_editor *e)
{
	if (SDL_WaitEvent(&e->event) != 0)
	{
		if (e->event.type == SDL_QUIT)
			return (wx_true);
		else if (e->event.type == SDL_KEYDOWN)
		{
			if (e->event.key.keysym.sym == SDLK_ESCAPE)
				return (wx_true);
			else
				we_key_event(e->event.key.keysym.sym, e);
		}
		else if (e->event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			we_editor_on_resize(e, e->event.window.data1,
								e->event.window.data2);
		else if (e->event.type == SDL_MOUSEMOTION)
			zz_mouse_event_move(e, e->event.motion.x, e->event.motion.y);
		else if (e->event.type == SDL_MOUSEBUTTONDOWN)
			zz_mouse_event_click(e, e->event.button.x, e->event.button.y);
		else if (e->event.type == SDL_MOUSEBUTTONUP)
			we_mouse_button_up(&e->map.ptr_hold, e->event.button.button);
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
			we_draw(e);
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
		e->quit = zz_wait_event(e);
	}
	return (wx_true);
}
