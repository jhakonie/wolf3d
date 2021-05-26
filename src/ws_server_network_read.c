/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ws_server_network_read.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 12:11:36 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 15:44:07 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ws_server.h"

static void	zz_remote_clients_reap_timedout(t_server *s, t_f64 time_s,
	t_f64 timeout_s)
{
	t_u64			i;
	t_remote_client	*rc;

	i = 0;
	while (i < s->remote_clients_size)
	{
		rc = &s->remote_clients[i];
		if (rc->state == ws_disconnected
			|| time_s - rc->packet_time_s < timeout_s)
		{
			++i;
			continue ;
		}
		wx_buffer_set(rc, sizeof(*rc), 0);
		rc->state = ws_disconnected;
		--s->remote_clients_connected_count;
		++i;
	}
}

static t_remote_client	*zz_remote_clients_insert(t_server *s,
	t_packet const *p)
{
	t_u64			i;
	t_remote_client	*rc;

	i = 0;
	while (i < s->remote_clients_size)
	{
		rc = &s->remote_clients[i];
		if (rc->state != ws_disconnected)
		{
			++i;
			continue ;
		}
		rc->state = ws_connected;
		rc->address = p->address;
		rc->address_size = p->address_size;
		rc->packet_time_s = 0.0f;
		rc->orientation = (t_q4){0.0f, 0.0f, 0.0f, 1.0f};
		rc->position = (t_p3){0.0f, 0.0f, 0.0f};
		++s->remote_clients_connected_count;
		return (rc);
		++i;
	}
	return (WX_NULL);
}

static t_remote_client	*zz_remote_clients_lookup(t_server *s,
	t_packet const *p)
{
	t_u64			i;
	t_remote_client	*rc;

	i = 0;
	while (i < s->remote_clients_size)
	{
		rc = &s->remote_clients[i];
		if (rc->state == ws_connected && wx_address_equal(&rc->address,
				rc->address_size, &p->address, p->address_size))
		{
			return (rc);
		}
		++i;
	}
	return (zz_remote_clients_insert(s, p));
}

/*
** 2021-02-14 todo: does there need to be an upperbound on how much time can be
** spent here. it would be nice to expect that in practice there are only
** handful of packets queued. in theory it could be possible to get the game
** stuck here by somehow generating infinitely many packets
*/

void	ws_server_network_read(t_server *s, t_f64 packet_time_s)
{
	t_u64			i;
	t_packet		p;
	t_remote_client	*rc;

	zz_remote_clients_reap_timedout(s, packet_time_s,
		s->remote_client_timeout_s);
	while (wx_true)
	{
		if (!wx_socket_read(s->socket, &p))
			break ;
		if (!p.size)
			break ;
		rc = zz_remote_clients_lookup(s, &p);
		if (!rc)
			continue ;
		i = 0;
		wx_packet_read_q4(&p, &i, &rc->orientation);
		wx_packet_read_u8(&p, &i, (t_u8 *)&rc->input.move_up);
		wx_packet_read_u8(&p, &i, (t_u8 *)&rc->input.move_down);
		wx_packet_read_u8(&p, &i, (t_u8 *)&rc->input.move_left);
		wx_packet_read_u8(&p, &i, (t_u8 *)&rc->input.move_right);
		rc->packet_time_s = packet_time_s;
	}
}
