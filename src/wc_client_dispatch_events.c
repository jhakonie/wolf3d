/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_client_dispatch_events.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:53:50 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 14:34:28 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_client.h"
#include "wc_draw.h"

/*
** 2021-02-17 todo: remove?
*/

static void	zz_on_expose(t_client *c)
{
	wc_draw_copy(c, &c->frame_buffer);
}

static void	zz_on_key(t_client *c, SDL_KeyboardEvent *k, t_bool down)
{
	if (k->keysym.sym == SDLK_ESCAPE && down)
		c->run = wx_false;
	else if (k->keysym.sym == SDLK_w)
		c->input.move_up = down;
	else if (k->keysym.sym == SDLK_a)
		c->input.move_left = down;
	else if (k->keysym.sym == SDLK_s)
		c->input.move_down = down;
	else if (k->keysym.sym == SDLK_d)
		c->input.move_right = down;
}

/*
** SDL_DestroyRenderer() frees related textures
*/

static void	zz_on_resize(t_client *c, t_s32 width, t_s32 height)
{
	SDL_DestroyRenderer(c->renderer);
	c->renderer = SDL_CreateRenderer(c->window, -1, 0);
	if (!c->renderer)
	{
		c->run = wx_false;
	}
	c->texture = SDL_CreateTexture(c->renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, width, height);
	if (!c->texture)
	{
		c->run = wx_false;
	}
	free(c->frame_buffer.data);
	c->frame_buffer.data = WX_NULL;
	c->frame_buffer.data_size = width * height * 4;
	c->frame_buffer.data = (t_u8 *)malloc(c->frame_buffer.data_size);
	if (!c->frame_buffer.data)
	{
		c->run = wx_false;
	}
	wx_buffer_set(c->frame_buffer.data, c->frame_buffer.data_size, 0);
	c->frame_buffer.width = width;
	c->frame_buffer.height = height;
}

static void	zz_on_windowevent(t_client *c, SDL_WindowEvent *w)
{
	if (w->event == SDL_WINDOWEVENT_EXPOSED)
	{
		zz_on_expose(c);
	}
	else if (w->event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		zz_on_resize(c, w->data1, w->data2);
	}
}

/*
** 2021-02-14 todo: does there need to be an upperbound on how much time can be
** spent here. it would be nice to expect that in practice there are only
** handful of events queued. in theory it could be possible to get the game
** stuck here by somehow generating infinitely many events
*/

void	wc_client_dispatch_events(t_client *c)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			c->run = wx_false;
			break ;
		}
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
			zz_on_key(c, &e.key, e.type == SDL_KEYDOWN);
		else if (e.type == SDL_WINDOWEVENT)
			zz_on_windowevent(c, &e.window);
	}
}
