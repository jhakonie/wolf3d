/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_client_dispatch_events.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:53:50 by name          #+#    #+#             */
/*   Updated: 2021/06/20 17:49:45 by jhakonie         ###   ########.fr       */
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

static void	zz_on_key(t_client *c, SDL_KeyboardEvent const *k, t_bool down)
{
	if (k->keysym.sym == SDLK_ESCAPE && down)
		c->run = wx_false;
	else if (k->keysym.sym == SDLK_w || k->keysym.sym == SDLK_UP)
		c->input.move_forward = down;
	else if (k->keysym.sym == SDLK_a)
		c->input.move_left = down;
	else if (k->keysym.sym == SDLK_s || k->keysym.sym == SDLK_DOWN)
		c->input.move_backward = down;
	else if (k->keysym.sym == SDLK_d)
		c->input.move_right = down;
	else if (k->keysym.sym == SDLK_LEFT && down)
		c->mouse_dx -= 10;
	else if (k->keysym.sym == SDLK_RIGHT && down)
		c->mouse_dx += 10;
	else if (k->keysym.sym == SDLK_m && down)
	{
		SDL_SetRelativeMouseMode(!SDL_GetRelativeMouseMode());
		c->mouse_captured ^= wx_true;
	}
	else if (k->keysym.sym == SDLK_SPACE && down)
		c->input.move_mode = (c->input.move_mode + 1) % 2;
}

static void	zz_on_mouse(t_client *c, SDL_MouseMotionEvent const *m)
{
	if (!c->mouse_captured)
		return ;
	c->mouse_x = m->x;
	c->mouse_y = m->y;
	c->mouse_dx += m->xrel;
	c->mouse_dy += m->yrel;
}

static void	zz_on_windowevent(t_client *c, SDL_WindowEvent *w)
{
	if (w->event == SDL_WINDOWEVENT_EXPOSED)
	{
		zz_on_expose(c);
	}
	else if (w->event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		wc_client_on_resize(c, w->data1, w->data2);
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

	c->mouse_dx = 0;
	c->mouse_dy = 0;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			c->run = wx_false;
			break ;
		}
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
			zz_on_key(c, &e.key, e.type == SDL_KEYDOWN);
		else if (e.type == SDL_MOUSEMOTION)
			zz_on_mouse(c, &e.motion);
		else if (e.type == SDL_WINDOWEVENT)
			zz_on_windowevent(c, &e.window);
	}
}
