/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_remote_server_del.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: name <name@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 18:34:19 by name          #+#    #+#             */
/*   Updated: 2021/02/06 12:47:50 by name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

#include "wc_client.h"

void	wc_remote_server_del(t_remote_server *rs)
{
	wx_buffer_set(&rs->address, sizeof(rs->address), 0);
	rs->address_size = 0;
	close(rs->socket);
	rs->socket = -1;
}
