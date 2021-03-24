/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_socket_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 13:48:48 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 15:55:04 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errno.h"

#include "wx_net.h"

t_bool	wx_socket_read(int socket, t_packet *p)
{
	ssize_t	status;

	p->address_size = sizeof(p->address);
	status = recvfrom(socket, p->buffer, WX_PACKET_BUFFER_SIZE - 1, 0,
			&p->address, &p->address_size);
	if (status == -1 && errno != EWOULDBLOCK)
	{
		return (wx_false);
	}
	else if (status == -1 && errno == EWOULDBLOCK)
	{
		status = 0;
	}
	p->buffer[status] = '\0';
	p->size = status;
	return (wx_true);
}
