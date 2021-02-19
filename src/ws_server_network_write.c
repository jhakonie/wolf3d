/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ws_server_network_write.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 12:27:49 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/19 18:36:06 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ws_server.h"

static void	zz_packet_write_others(t_packet *p, t_remote_client *rcs,
	t_u64 rcs_size, t_u64 i_)
{
	t_u64			i;
	t_remote_client	*rc;

	i = 0;
	while (i < rcs_size)
	{
		rc = &rcs[i];
		if (rc->state != ws_connected || i == i_)
		{
			++i;
			continue ;
		}
		wx_packet_write_v2(p, &rc->position);
		++i;
	}
}

void		ws_server_network_write(t_server *s)
{
	t_u64			i;
	t_packet		p;
	t_remote_client	*rc;

	i = 0;
	while (i < s->remote_clients_size)
	{
		rc = &s->remote_clients[i];
		if (rc->state != ws_connected)
		{
			++i;
			continue ;
		}
		p.address = rc->address;
		p.address_size = rc->address_size;
		p.size = 0;
		wx_packet_write_v2(&p, &rc->position);
		wx_packet_write_u8(&p, s->remote_clients_connected_count - 1);
		zz_packet_write_others(&p, s->remote_clients, s->remote_clients_size,
			i);
		if (!wx_socket_write(s->socket, &p))
		{
		}
		++i;
	}
}