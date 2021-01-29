/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ws_server.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 23:54:46 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/01/28 05:15:41 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WS_SERVER_H
# define WS_SERVER_H

# include "wx_types.h"

struct	s_server
{
	t_bool		run;
};
typedef struct s_server	t_server;

t_bool	ws_server_new(t_server *s);
void	ws_server_del(t_server *s);

#endif
