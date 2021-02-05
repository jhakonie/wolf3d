/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_net.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:23:06 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/05 14:06:49 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WX_NET_H
# define WX_NET_H

# include "sys/socket.h"

# include "wx_types.h"

# define WX_PACKET_BUFFER_SIZE (1024)

struct	s_packet
{
	struct sockaddr		addr;
	socklen_t			addr_size;
	t_u8				buffer[WX_PACKET_BUFFER_SIZE];
	t_u64				size;
};
typedef struct s_packet	t_packet;

t_bool	wx_net_read(int socket, t_packet *p);
t_bool	wx_net_write(int socket, t_packet const *p);

#endif
