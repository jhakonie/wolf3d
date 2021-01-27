/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_client_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:27:18 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/01/27 11:40:06 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_client.h"

static void		zz_draw(t_client *c)
{
	(void)c;
	c->draw = wx_false;
}

static void		zz_on_keydown(t_client *c)
{
	if (c->event.key.keysym.sym == SDLK_ESCAPE)
		c->run = wx_false;
}

static void		zz_on_windowevent(t_client *c)
{
	if (c->event.window.event == SDL_WINDOWEVENT_EXPOSED)
	{
		wc_client_on_expose(c);
		c->draw = wx_true;
	}
	else if (c->event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		wc_client_on_resize(c, c->event.window.data1,
			c->event.window.data2);
		c->draw = wx_true;
	}
}

t_bool			wc_client_run(t_client *g)
{
	while (g->run)
	{
		while (SDL_PollEvent(&g->event))
		{
			if (g->event.type == SDL_QUIT)
			{
				g->run = wx_false;
				break ;
			}
			else if (g->event.type == SDL_KEYDOWN)
				zz_on_keydown(g);
			else if (g->event.type == SDL_WINDOWEVENT)
				zz_on_windowevent(g);
		}
		if (g->run && g->draw)
			zz_draw(g);
	}
	return (wx_true);
}
