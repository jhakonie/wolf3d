/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_remote_server_del.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 18:34:19 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/05 18:35:02 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

#include "wc_client.h"

void	wc_remote_server_del(t_remote_server *rs)
{
	wx_buffer_set(&rs->address, sizeof(rs->address), 0);
	rs->address_size = 0;
	close(rs->fd);
	rs->fd = -1;
}
