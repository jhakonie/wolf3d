/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_client_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:27:18 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 14:39:17 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys/socket.h"
#include "netdb.h"
#include "unistd.h"

#include "wc_client.h"
#include "wx_time.h"

/*
** 2021-02-17 todo: when running two instances of wolf3d and hitting esc the
** event gets reported to both windows if they are one after the other in the
** windows mru. resulting in both windows closing! would be nice to fix this.
** happens on different wm? happens on macos?
*/

static void	zz_client_move_mode(t_client *c)
{
	if (c->move_mode == wx_client_move_mode_2d)
	{
		c->draw = &wc_draw_25d;
		c->player_orientation = wx_q4_new_v3_f32(&(t_v3){0.0f, 1.0f, 0.0f},
				wx_q4_yrot(&c->player_orientation));
	}
	else
	{
		c->draw = &wc_draw_3d;
	}
}

static void	zz_integrate(t_client *c)
{
	t_v3	axis;
	t_q4	rotation;

	axis = (t_v3){0.0f, 1.0f, 0.0f};
	rotation = wx_q4_new_v3_f32(&axis, -0.01 * c->mouse_dx);
	c->player_orientation = wx_q4_mul_q4(&rotation, &c->player_orientation);
	axis = (t_v3){1.0f, 0.0f, 0.0f};
	rotation = wx_q4_new_v3_f32(&axis, 0.01 * c->mouse_dy);
	c->player_orientation = wx_q4_mul_q4(&c->player_orientation, &rotation);
	zz_client_move_mode(c);
	wx_q4_normalize(&c->player_orientation);
	if (c->sim_time_accumulator_s >= c->sim_time_step_s)
	{
		c->sim_time_s += c->sim_time_step_s;
		c->sim_time_accumulator_s -= c->sim_time_step_s;
	}
}

static void	zz_network(t_client *c)
{
	t_u8				i;
	t_packet			p;

	if (c->net_time_accumulator_s >= c->net_time_step_s)
	{
		c->net_time_accumulator_s -= c->net_time_step_s;
		wc_remote_server_write(&c->remote_server, &c->input,
			&c->player_orientation);
	}
	while (wc_remote_server_read(&c->remote_server, &p))
	{
		p.read_i = 0;
		wx_packet_read_u64(&p, &p.read_seq);
		wx_packet_read_u8(&p, (t_u8 *)&c->move_mode);
		wx_packet_read_p3(&p, &c->player_position);
		wx_packet_read_u8(&p, &c->others_size);
		i = 0;
		while (i < c->others_size)
		{
			wx_packet_read_q4(&p, &c->other_orientations[i]);
			wx_packet_read_p3(&p, &c->other_positions[i]);
			++i;
		}
	}
}

t_bool	wc_client_run(t_client *c)
{
	t_f64		real_delta_s;
	t_f64		real_time0_s;
	t_f64		real_time1_s;

	real_time0_s = c->sim_time_s;
	while (c->run)
	{
		real_time1_s = wx_time_s();
		real_delta_s = wx_f64_min(real_time1_s - real_time0_s, 3.0
				* c->sim_time_step_s);
		real_time0_s = real_time1_s;
		c->net_time_accumulator_s += real_delta_s;
		c->sim_time_accumulator_s += real_delta_s;
		wc_client_dispatch_events(c);
		zz_network(c);
		zz_integrate(c);
		c->draw(c);
	}
	return (wx_true);
}
