/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_m44_new_perspective.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 21:04:19 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 15:50:02 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

#include "wx_math.h"

/*
** 2021-03-15 note: distance where:
** - x spans +/- aspect_ratio
** - y spans to +/- 1
*/

static t_f32	zz_projection_plane_distance(t_f32 hfov_rad, t_f32 aspect_ratio)
{
	t_f32	d;
	t_f32	vfov_rad;

	vfov_rad = 2 * atanf(tanf(0.5f * hfov_rad) / aspect_ratio);
	d = 1.0f / tanf(0.5f * vfov_rad);
	return (d);
}

/*
** 2021-03-03 note: the resulting perspective projection matrix sets up a
** mapping:
** - view z near to ndc z 1
** - view z far to ndc z 0
** once they've gone through the perspective divide
**
** 202103-15 note: it is possible to recover the values from the matrix:
** - aspect_ratio = m.xs[5] / m.xs[0];
** - hfov_deg = 2 * atanf(1.0 / m.xs[0]) * (180.0f / PI);
** - vfov_deg = 2 * atanf(1.0 / m.xs[5]) * (180.0f / PI);

*/

t_m44	wx_m44_new_perspective(t_f32 hfov_rad, t_f32 aspect_ratio, t_f32 near,
	t_f32 far)
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
