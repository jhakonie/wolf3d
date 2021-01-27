/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_client_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:27:18 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/01/27 13:07:30 by ***REMOVED***         ###   ########.fr       */
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

t_bool			wc_client_run(t_client *c)
{
	while (c->run)
	{
		while (SDL_PollEvent(&c->event))
		{
			if (c->event.type == SDL_QUIT)
			{
				c->run = wx_false;
				break ;
			}
			else if (c->event.type == SDL_KEYDOWN)
				zz_on_keydown(c);
			else if (c->event.type == SDL_WINDOWEVENT)
				zz_on_windowevent(c);
		}
		if (c->run && c->draw)
			zz_draw(c);
	}
	return (wx_true);
}
