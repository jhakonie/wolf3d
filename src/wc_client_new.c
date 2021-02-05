/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_client_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:17:11 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/05 19:07:18 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_client.h"

static t_bool	zz_on_error(t_client *c, t_u8 i)
{
	if (i > 4)
	{
		wx_frame_buffer_del(&c->frame_buffer);
	}
	if (i > 3)
	{
		SDL_DestroyTexture(c->texture);
	}
	if (i > 2)
	{
		SDL_DestroyRenderer(c->renderer);
	}
	if (i > 1)
	{
		SDL_DestroyWindow(c->window);
	}
	if (i > 0)
	{
		SDL_Quit();
	}
	return (wx_false);
}

t_bool			wc_client_new(t_client *c, t_u32 window_width,
	t_u32 window_height)
{
	wx_buffer_set(c, sizeof(*c), 0);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (zz_on_error(c, 0));
	if (!(c->window = SDL_CreateWindow("wolf3d_client", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, window_width, window_height, 0)))
		return (zz_on_error(c, 1));
	if (!(c->renderer = SDL_CreateRenderer(c->window, -1, 0)))
		return (zz_on_error(c, 2));
	if (!(c->texture = SDL_CreateTexture(c->renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING, window_width, window_height)))
		return (zz_on_error(c, 3));
	if (!wx_frame_buffer_new(&c->frame_buffer, window_width, window_height))
		return (zz_on_error(c, 4));
	if (!wc_remote_server_new(&c->remote_server, "localhost", "12345"))
		return (zz_on_error(c, 5));
	c->draw = wx_true;
	c->run = wx_true;
	return (wx_true);
}
