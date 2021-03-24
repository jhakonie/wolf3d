/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_frustum_aabb_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:10:32 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 15:48:31 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

#include "wx_math.h"

/*
** 2021-03-22 note: this test implementation calculates effectively a boudning
** sphere around the aabb per every tested plane. the radius of the sphere
** varies based on the aabb's projection onto the plane's normal. this way an
** overly tall/thin aabb causes fewer false positives. false positive meaning
** aabb is marked visible (wx_true) when it is just slightly outside the frustum
**
** 2021-03-22 todo: implement a test that returns a clip_state indicating each
** plane the aabb crossed. this can be used later on in the pipeline when
** clipping triangles to reduce number of tests to perform
*/

t_bool	wx_frustum_aabb_test(t_frustum const *f, t_aabb const *object_aabb,
	t_m44 const *view_from_object)
{
	t_u64			i;
	t_u64			j;
	t_obb			obb;
	t_f32			projected_size;

	obb = wx_obb_new(object_aabb, view_from_object);
	i = 0;
	while (i < 6)
	{
		projected_size = 0;
		j = 0;
		while (j < 3)
		{
			projected_size += obb.extents2[j]
				* fabsf(wx_plane_signed_distance_n3(f->planes + i, obb.axes
						+ j));
			++j;
		}
		if (wx_plane_signed_distance_p3(f->planes + i, &obb.center)
			< -projected_size)
			return (wx_false);
		++i;
	}
	return (wx_true);
}
