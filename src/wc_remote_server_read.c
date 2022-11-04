/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_remote_server_read.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: name <name@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:54:18 by name          #+#    #+#             */
/*   Updated: 2021/03/24 14:58:00 by name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_client.h"

t_bool	wc_remote_server_read(t_remote_server *rs, t_packet *p)
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
