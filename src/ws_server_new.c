/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ws_server_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 04:42:55 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/05 11:30:54 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "netdb.h"
#include "unistd.h"

#include "ws_server.h"

static t_bool	zz_socket_bind(int *s, struct addrinfo *interfaces)
{
	struct addrinfo			*i;

	i = interfaces;
	while (i)
	{
		if ((*s = socket(i->ai_family, i->ai_socktype, i->ai_protocol)) == -1)
			continue ;
		if (bind(*s, i->ai_addr, i->ai_addrlen) == -1)
		{
			close(*s);
			continue ;
		}
		break ;
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

t_bool			ws_server_new(t_server *s)
{
	wx_buffer_set(s, sizeof(*s), 0);
	if (!zz_socket_new(&s->socket, "12345"))
	{
		return (wx_false);
	}
	s->run = wx_true;
	return (wx_true);
}
