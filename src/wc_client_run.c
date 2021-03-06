/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_client_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:27:18 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/05 12:52:37 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys/socket.h"
#include "netdb.h"
#include "unistd.h"

#include "wc_client.h"
#include "wc_draw.h"
#include "wx_net.h"
#include "wx_time.h"

/*
** 2021-02-17 todo: when running two instances of wolf3d and hitting esc the
** event gets reported to both windows if they are one after the other in the
** windows mru. resulting in both windows closing! would be nice to fix this.
** happens on different wm? happens on macos?
*/

static void		zz_integrate(t_client *c)
{
	if (c->sim_time_accumulator_s >= c->sim_time_step_s)
	{
		c->sim_time_s += c->sim_time_step_s;
		c->sim_time_accumulator_s -= c->sim_time_step_s;
	}
}

static void		zz_network(t_client *c)
{
	t_u8		i;
	t_u64		p_offset;
	t_packet	p;

	wc_remote_server_write(&c->remote_server, &c->input);
	if (wc_remote_server_read(&c->remote_server, &p))
	{
		p_offset = 0;
		wx_packet_read_p2(&p, &p_offset, &c->player_position);
		wx_packet_read_u8(&p, &p_offset, &c->other_positions_size);
		i = 0;
		while (i < c->other_positions_size)
		{
			wx_packet_read_p2(&p, &p_offset, &c->other_positions[i]);
			++i;
		}
	}
}

t_bool			wc_client_run(t_client *c)
{
	t_f64		sim_delta_s;
	t_f64		real_time0_s;
	t_f64		real_time1_s;

	real_time0_s = c->sim_time_s;
	while (c->run)
	{
		real_time1_s = wx_time_s();
		sim_delta_s = wx_f64_min(real_time1_s - real_time0_s, 3.0 *
			c->sim_time_step_s);
		real_time0_s = real_time1_s;
		c->sim_time_accumulator_s += sim_delta_s;
		wc_client_dispatch_events(c);
		zz_network(c);
		zz_integrate(c);
		wc_draw(c);
	}
	return (wx_true);
}
