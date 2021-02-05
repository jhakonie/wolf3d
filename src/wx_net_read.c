/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_net_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 13:48:48 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/05 17:13:27 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_net.h"

t_bool	wx_net_read(int socket, t_packet *p)
{
	ssize_t					status;

	p->addr_size = sizeof(p->addr);
	if ((status = recvfrom(socket, p->buffer, WX_PACKET_BUFFER_SIZE - 1, 0,
		&p->addr, &p->addr_size)) == -1)
	{
		return (wx_false);
	}
	p->buffer[status] = '\0';
	p->size = status;
	return (wx_true);
}
