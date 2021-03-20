/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_frustum_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 08:01:41 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/20 08:03:50 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_math.h"

/*
** 2021-03-20 note: modified gribb-hartmann due to different z-axis direction?
** near and far seem to be switched compared to the original paper
*/

t_frustum	wx_frustum_new(t_m44 const *m)
{
	t_frustum	f;

	f.planes[0] = wx_plane_new(m->xs[3] - m->xs[0], m->xs[7] - m->xs[4],
		m->xs[11] - m->xs[8], m->xs[15] - m->xs[12]);
	f.planes[1] = wx_plane_new(m->xs[3] + m->xs[0], m->xs[7] + m->xs[4],
		m->xs[11] + m->xs[8], m->xs[15] + m->xs[12]);
	f.planes[2] = wx_plane_new(m->xs[3] + m->xs[1], m->xs[7] + m->xs[5],
		m->xs[11] + m->xs[9], m->xs[15] + m->xs[13]);
	f.planes[3] = wx_plane_new(m->xs[3] - m->xs[1], m->xs[7] - m->xs[5],
		m->xs[11] - m->xs[9], m->xs[15] - m->xs[13]);
	f.planes[4] = wx_plane_new(m->xs[3] - m->xs[2], m->xs[7] - m->xs[6],
		m->xs[11] - m->xs[10], m->xs[15] - m->xs[14]);
	f.planes[5] = wx_plane_new(m->xs[2], m->xs[6], m->xs[10], m->xs[14]);
	return (f);
}
