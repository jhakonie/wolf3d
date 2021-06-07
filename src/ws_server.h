/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ws_server.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 23:54:46 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 15:42:14 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WS_SERVER_H
# define WS_SERVER_H

# include "sys/socket.h"

# include "wx_math.h"
# include "wx_net.h"
# include "wx_types.h"

enum	e_remote_client_state
{
	ws_disconnected,
	ws_connected
};
typedef enum e_remote_client_state	t_remote_client_state;

struct	s_remote_client
{
	t_remote_client_state	state;
	struct sockaddr			address;
	socklen_t				address_size;
	t_u64					received_packet_seq;
	t_client_input			input;
	t_f64					packet_time_s;
	t_q4					orientation;
	t_p3					position;
};
typedef struct s_remote_client		t_remote_client;

struct	s_server
{
	t_remote_client	remote_clients[WX_SERVER_REMOTE_CLIENTS_SIZE];
	t_u64			remote_clients_size;
	t_u64			remote_clients_connected_count;
	t_f64			remote_client_timeout_s;
	t_bool			run;
	int				socket;
	t_u64			sent_packet_seq;
	t_f64			sim_time_s;
	t_f64			sim_time_accumulator_s;
	t_f64			sim_time_step_s;
};
typedef struct s_server				t_server;

t_bool	ws_server_new(t_server *s);
void	ws_server_del(t_server *s);
void	ws_server_network_read(t_server *s, t_f64 packet_time_s);
void	ws_server_network_write(t_server *s);
t_bool	ws_server_run(t_server *s);

#endif
