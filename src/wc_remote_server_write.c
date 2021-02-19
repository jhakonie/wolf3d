/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_remote_server_write.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:17:29 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/17 10:30:42 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_client.h"

t_bool	wc_remote_server_write(t_remote_server *rs, t_client_input const *ci)
{
	t_packet	p;

	p.address = rs->address;
	p.address_size = rs->address_size;
	p.size = 0;
	wx_packet_write_u8(&p, ci->move_up);
	wx_packet_write_u8(&p, ci->move_down);
	wx_packet_write_u8(&p, ci->move_left);
	wx_packet_write_u8(&p, ci->move_right);
	if (!wx_socket_write(rs->socket, &p))
	{
		return (wx_false);
	}
	return (wx_true);
}