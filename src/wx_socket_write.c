/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_socket_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 13:50:47 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 15:55:23 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_net.h"

t_bool	wx_socket_write(int socket, t_packet const *p)
{
	t_u64	sent_size;
	ssize_t	status;

	sent_size = 0;
	while (sent_size != p->size)
	{
		status = sendto(socket, p->buffer + sent_size, p->size - sent_size, 0,
				&p->address, p->address_size);
		if (status == -1)
		{
			return (wx_false);
		}
		sent_size += status;
	}
	return (wx_true);
}
