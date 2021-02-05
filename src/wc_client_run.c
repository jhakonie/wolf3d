/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_client_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:27:18 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/05 19:12:41 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys/socket.h"
#include "netdb.h"
#include "unistd.h"

#include "wc_client.h"
#include "wx_net.h"

static void	zz_draw(t_client *c)
{
	(void)c;
	c->draw = wx_false;
}

static void	zz_on_keydown(t_client *c)
{
	if (c->event.key.keysym.sym == SDLK_ESCAPE)
		c->run = wx_false;
}

static void	zz_on_windowevent(t_client *c)
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

static void	zz_send_packet(t_client *c)
{
	t_packet		packet;

	packet.addr = c->remote_server.address;
	packet.addr_size = c->remote_server.address_size;
	wx_buffer_copy(packet.buffer, "abc", 3);
	packet.size = 3;
	if (!wx_net_write(c->remote_server.fd, &packet))
	{
		c->run = wx_false;
	}
}

t_bool		wc_client_run(t_client *c)
{
	while (c->run)
	{
		zz_send_packet(c);
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
		SDL_Delay(1000);
	}
	return (wx_true);
}
