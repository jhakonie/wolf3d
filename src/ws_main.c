/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ws_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:44:53 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/05 19:20:12 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

#include "wx_net.h"
#include "ws_server.h"

static void	zz_print(char const *xs)
{
	t_u64	i;

	i = 0;
	while (xs[i])
	{
		++i;
	}
	write(1, xs, i);
}

int			main(void)
{
	t_packet	p;
	t_server	s;

	if (!ws_server_new(&s))
	{
		return (-1);
	}
	while (s.run)
	{
		zz_print("blocking...\n");
		if (!wx_net_read(s.socket, &p))
		{
			s.run = wx_false;
			break ;
		}
		zz_print((char const *)p.buffer);
		zz_print("\n");
	}
	ws_server_del(&s);
	return (0);
}
