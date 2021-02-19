/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_remote_server_read.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:54:18 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/17 10:42:01 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_client.h"

t_bool			wc_remote_server_read(t_remote_server *rs, t_packet *p)
{
	if (!wx_socket_read(rs->socket, p))
	{
		return (wx_false);
	}
	if (!p->size)
	{
		return (wx_false);
	}
	if (!wx_address_equal(&rs->address, rs->address_size, &p->address,
		p->address_size))
	{
		return (wx_false);
	}
	return (wx_true);
}
