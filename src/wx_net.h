/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_net.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 17:23:06 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 15:53:08 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WX_NET_H
# define WX_NET_H

# include "sys/socket.h"

# include "wx_math.h"
# include "wx_types.h"

# define WX_PACKET_BUFFER_SIZE (1024)
# define WX_SERVER_REMOTE_CLIENTS_SIZE (4)
# define WX_SERVER_DEFAULT_SOCKET ("12345")

struct	s_client_input
{
	t_bool	move_up;
	t_bool	move_down;
	t_bool	move_left;
	t_bool	move_right;
};
typedef struct s_client_input	t_client_input;

struct	s_packet
{
	struct sockaddr		address;
	socklen_t			address_size;
	t_u8				buffer[WX_PACKET_BUFFER_SIZE];
	t_u64				size;
};
typedef struct s_packet			t_packet;

void	wx_packet_read_f32(t_packet *p, t_u64 *i, t_f32 *x);
void	wx_packet_read_p2(t_packet *p, t_u64 *i, t_p2 *x);
void	wx_packet_read_u8(t_packet *p, t_u64 *i, t_u8 *x);
void	wx_packet_write_f32(t_packet *p, t_f32 x);
void	wx_packet_write_p2(t_packet *p, t_p2 const *x);
void	wx_packet_write_u8(t_packet *p, t_u8 x);

struct	s_server_update
{
	t_p2	client_position;
	t_p2	other_positions[WX_SERVER_REMOTE_CLIENTS_SIZE - 1];
	t_u8	other_positions_size;
};
typedef struct s_server_update	t_server_update;

t_bool	wx_address_equal(struct sockaddr const *a0, socklen_t a0_size,
			struct sockaddr const *a1, socklen_t a1_size);
t_bool	wx_socket_read(int socket, t_packet *p);
t_bool	wx_socket_write(int socket, t_packet const *p);

#endif
