/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_remote_server_new.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 18:33:06 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/05 19:02:09 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "netdb.h"

#include "wc_client.h"

static struct addrinfo	*zz_socket_new(int *s, struct addrinfo *as)
{
	struct addrinfo *i;

	i = as;
	while (i)
	{
		if ((*s = socket(i->ai_family, i->ai_socktype, i->ai_protocol)) != -1)
			break ;
		i = i->ai_next;
	}
	return (i);
}

t_bool					wc_remote_server_new(t_remote_server *rs,
	char const *hostname, char const *port)
{
	struct addrinfo	hints;
	struct addrinfo *i;
	struct addrinfo	*server_infos;

	wx_buffer_set(&hints, sizeof(hints), 0);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	if (getaddrinfo(hostname, port, &hints, &server_infos) != 0)
		return (wx_false);
	if (!(i = zz_socket_new(&rs->fd, server_infos)))
	{
		freeaddrinfo(server_infos);
		return (wx_false);
	}
	rs->address = *i->ai_addr;
	rs->address_size = i->ai_addrlen;
	freeaddrinfo(server_infos);
	return (wx_true);
}
