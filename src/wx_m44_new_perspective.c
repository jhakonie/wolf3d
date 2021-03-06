/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_m44_new_perspective.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 21:04:19 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/06 14:49:09 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

#include "wx_math.h"

static t_f32	zz_projection_plane_distance(t_f32 hfov_rad, t_f32 aspect_ratio)
{
	t_f32	d;

	d = aspect_ratio / tan(0.5 * hfov_rad);
	return (d);
}

/*
** 2021-03-03 note: the resulting perspective projection matrix sets up a
** mapping:
** - view z near to ndc z 1
** - view z far to ndc z 0
** once they've gone through the perspective divide
*/

t_m44			wx_m44_new_perspective(t_f32 hfov_rad, t_f32 aspect_ratio,
	t_f32 near, t_f32 far)
{
	t_f32	ppd;
	t_m44	m;

	wx_buffer_set(m.xs, sizeof(m.xs), 0);
	ppd = zz_projection_plane_distance(hfov_rad, aspect_ratio);
	m.xs[0] = ppd / aspect_ratio;
	m.xs[5] = ppd;
	m.xs[10] = near / (near - far);
	m.xs[11] = 1.0f;
	m.xs[14] = (far * near) / (far - near);
	return (m);
}
