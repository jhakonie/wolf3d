/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ws_server_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 23:46:11 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 15:46:16 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ws_server.h"
#include "wx_time.h"

static void	zz_remote_client_integrate(t_remote_client *rc, t_f64 time_step_s)
{
	t_v3	v;

	v = (t_v3){0.0f, 0.0f, 0.0f};
	if (rc->input.move_up)
		v.z += 10.0f * time_step_s;
	if (rc->input.move_down)
		v.z -= 10.0f * time_step_s;
	if (rc->input.move_left)
		v.x += 10.0f * time_step_s;
	if (rc->input.move_right)
		v.x -= 10.0f * time_step_s;
	v = wx_q4_rot_v3(&rc->orientation, &v);
	rc->position = wx_p3_add_v3(&rc->position, &v);
}

/*
** 2021-05-23 todo: normalize velocity vector so diagonal movement does not gain
** advantage
*/
static void	zz_integrate(t_remote_client *rcs, t_u64 rcs_size, t_f64 time_s,
	t_f64 time_step_s)
{
	t_u64			i;
	t_remote_client	*rc;

	i = 0;
	while (i < rcs_size)
	{
		rc = &rcs[i];
		if (rc->state != ws_connected)
		{
			++i;
			continue ;
		}
		zz_remote_client_integrate(rc, time_step_s);
		++i;
	}
	(void)time_s;
}

t_bool	ws_server_run(t_server *s)
{
	t_f64	real_time0_s;
	t_f64	real_time1_s;
	t_f64	sim_delta_s;

	real_time0_s = s->sim_time_s;
	while (s->run)
	{
		real_time1_s = wx_time_s();
		sim_delta_s = wx_f64_min(real_time1_s - real_time0_s, 3.0
				* s->sim_time_step_s);
		real_time0_s = real_time1_s;
		s->sim_time_accumulator_s += sim_delta_s;
		ws_server_network_read(s, real_time0_s);
		if (s->sim_time_accumulator_s >= s->sim_time_step_s)
		{
			zz_integrate(s->remote_clients, s->remote_clients_size,
				s->sim_time_s, s->sim_time_step_s);
			s->sim_time_s += s->sim_time_step_s;
			s->sim_time_accumulator_s -= s->sim_time_step_s;
			ws_server_network_write(s);
		}
	}
	return (wx_true);
}
