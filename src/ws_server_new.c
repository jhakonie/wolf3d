/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ws_server_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 04:42:55 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 15:45:34 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fcntl.h"
#include "netdb.h"
#include "unistd.h"

#include "ws_server.h"
#include "wx_time.h"

static t_bool	zz_socket_bind(int *s, struct addrinfo *interfaces)
{
	struct addrinfo	*i;

	i = interfaces;
	while (i)
	{
		*s = socket(i->ai_family, i->ai_socktype, i->ai_protocol);
		if ((*s != -1)
			&& ((bind(*s, i->ai_addr, i->ai_addrlen) != -1))
			&& (fcntl(*s, F_SETFL, O_NONBLOCK) != -1))
		{
			break ;
		}
		close(*s);
		i = i->ai_next;
	}
	if (!i)
	{
		*s = -1;
		return (wx_false);
	}
	return (wx_true);
}

static t_bool	zz_socket_new(int *s, char const *port)
{
	struct addrinfo	hints;
	struct addrinfo	*interfaces;

	wx_buffer_set(&hints, sizeof(hints), 0);
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	if (getaddrinfo(WX_NULL, port, &hints, &interfaces) != 0)
		return (wx_false);
	if (!zz_socket_bind(s, interfaces))
	{
		return (wx_false);
		freeaddrinfo(interfaces);
	}
	freeaddrinfo(interfaces);
	return (wx_true);
}

t_bool	ws_server_new(t_server *s)
{
	wx_buffer_set(s, sizeof(*s), 0);
	s->remote_clients_size = WX_SERVER_REMOTE_CLIENTS_SIZE;
	s->remote_client_timeout_s = 3.0;
	if (!zz_socket_new(&s->socket, WX_SERVER_DEFAULT_SOCKET))
	{
		return (wx_false);
	}
	s->run = wx_true;
	s->sim_time_s = wx_time_s();
	s->sim_time_step_s = 1.0 / 30.0;
	return (wx_true);
}
