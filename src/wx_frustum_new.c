/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_frustum_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 08:01:41 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 15:49:01 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_math.h"

enum	e_frustum_plane
{
	wx_frustum_plane_left = 0,
	wx_frustum_plane_right = 1,
	wx_frustum_plane_bottom = 2,
	wx_frustum_plane_top = 3,
	wx_frustum_plane_near = 4,
	wx_frustum_plane_far = 5,
	wx_frustum_plane_max = 6
};
typedef enum e_frustum_plane	t_frustum_plane;

/*
** 2021-03-20 note: modified gribb-hartmann due to different z-axis direction?
** plane normals should point inside the frustum volume
**
** 2021-05-29 todo: not quite certain about the d component of the planes.
** seems to mostly work so guess it's alright?
*/
t_frustum	wx_frustum_new(t_m44 const *m)
{
	t_frustum	f;

	f.planes[wx_frustum_plane_left] = wx_plane_new(m->xs[3] - m->xs[0],
			m->xs[7] - m->xs[4], m->xs[11] - m->xs[8], m->xs[15] - m->xs[12]);
	f.planes[wx_frustum_plane_right] = wx_plane_new(m->xs[3] + m->xs[0],
			m->xs[7] + m->xs[4], m->xs[11] + m->xs[8], m->xs[15] + m->xs[12]);
	f.planes[wx_frustum_plane_bottom] = wx_plane_new(m->xs[3] + m->xs[1],
			m->xs[7] + m->xs[5], m->xs[11] + m->xs[9], m->xs[15] + m->xs[13]);
	f.planes[wx_frustum_plane_top] = wx_plane_new(m->xs[3] - m->xs[1],
			m->xs[7] - m->xs[5], m->xs[11] - m->xs[9], m->xs[15] - m->xs[13]);
	f.planes[wx_frustum_plane_near] = wx_plane_new(m->xs[3] - m->xs[2],
			m->xs[7] - m->xs[6], m->xs[11] - m->xs[10], m->xs[15] - m->xs[14]);
	f.planes[wx_frustum_plane_far] = wx_plane_new(m->xs[2], m->xs[6], m->xs[10],
			m->xs[14]);
	return (f);
}
