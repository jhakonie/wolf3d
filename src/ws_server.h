/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ws_server.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 23:54:46 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/05 11:11:29 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WS_SERVER_H
# define WS_SERVER_H

# include "sys/socket.h"

# include "wx_net.h"
# include "wx_types.h"

enum	e_remote_client_state
{
	wc_disconnected,
	wc_connected
};
typedef enum e_remote_client_state	t_remote_client_state;

struct	s_remote_client
{
	t_remote_client_state	state;
	struct sockaddr			address;
	socklen_t				address_size;
};
typedef struct s_remote_client	t_remote_client;

struct	s_server
{
	t_remote_client	remote_clients[4];
	t_bool			run;
	int				socket;
};
typedef struct s_server	t_server;

t_bool	ws_server_new(t_server *s);
void	ws_server_del(t_server *s);

#endif
