/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_frustum_aabb_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:10:32 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/30 06:52:53 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

#include "wx_math.h"

static t_plane_obb	zz_plane_obb_test(t_obb const *obb, t_plane const *p)
{
	t_f32	e2;
	t_f32	sd;

	e2 = obb->extents2[0] * fabsf(p->n.x) + obb->extents2[1] * fabsf(p->n.y)
		+ obb->extents2[2] * fabsf(p->n.z);
	sd = wx_plane_signed_distance_p3(p, &obb->center);
	if (sd + e2 < 0)
	{
		return (wx_plane_obb_out);
	}
	if (sd - e2 > 0)
	{
		return (wx_plane_obb_in);
	}
	return (wx_plane_obb_intersect);
}

t_frustum_aabb	wx_frustum_aabb_test(t_frustum const *f, t_aabb const *aabb,
	t_m44 const *b_from_a)
{
	t_frustum_aabb	fa;
	t_u64			i;
	t_obb			obb;
	t_plane_obb		po;

	fa = wx_frustum_aabb_all_out;
	obb = wx_obb_new(aabb, b_from_a);
	i = 0;
	while (i < 6)
	{
		po = zz_plane_obb_test(&obb, f->planes + i);
		if (po == wx_plane_obb_out)
			return (wx_frustum_aabb_all_out);
		else if (po == wx_plane_obb_intersect)
			fa |= 1 << i;
		++i;
	}
	if (fa == wx_frustum_aabb_all_out)
		return (wx_frustum_aabb_all_in);
	return (fa);
}
