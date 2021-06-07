/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_remote_server_new.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 18:33:06 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 14:57:22 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fcntl.h"
#include "netdb.h"
#include "unistd.h"

#include "wc_client.h"

static struct addrinfo	*zz_socket_new(int *s, struct addrinfo *as)
{
	struct addrinfo	*i;

	i = as;
	while (i)
	{
		*s = socket(i->ai_family, i->ai_socktype, i->ai_protocol);
		if ((*s != -1) && (fcntl(*s, F_SETFL, O_NONBLOCK) != -1))
		{
			break ;
		}
		close(*s);
		i = i->ai_next;
	}
	if (!i)
	{
		*s = -1;
	}
	return (i);
}

t_bool	wc_remote_server_new(t_remote_server *rs, char const *hostname,
	char const *port)
{
	struct addrinfo	hints;
	struct addrinfo	*i;
	struct addrinfo	*server_infos;

	wx_buffer_set(&hints, sizeof(hints), 0);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	if (getaddrinfo(hostname, port, &hints, &server_infos) != 0)
		return (wx_false);
	i = zz_socket_new(&rs->socket, server_infos);
	if (!i)
	{
		freeaddrinfo(server_infos);
		return (wx_false);
	}
	rs->address = *i->ai_addr;
	rs->address_size = i->ai_addrlen;
	freeaddrinfo(server_infos);
	rs->received_packet_seq = 0;
	rs->sent_packet_seq = 0;
	return (wx_true);
}
