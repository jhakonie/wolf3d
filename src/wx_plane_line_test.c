/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_plane_line_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 01:41:54 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/04/02 01:41:54 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_math.h"

t_plane_line	wx_plane_line_test(t_plane const *pl, t_p3 const *p0,
	t_p3 const *p1, t_f32 *t)
{
	t_f32	d0;
	t_f32	d1;

	d0 = wx_plane_signed_distance_p3(pl, p0);
	d1 = wx_plane_signed_distance_p3(pl, p1);
	if (d0 < 0.0f && d1 < 0.0f)
	{
		return (wx_plane_line_out);
	}
	if (d0 < 0.0f && d1 >= 0.0f)
	{
		*t = d0 / (d0 - d1);
		return (wx_plane_line_going_in);
	}
	if (d0 >= 0.0f && d1 < 0.0f)
	{
		*t = d0 / (d0 - d1);
		return (wx_plane_line_going_out);
	}
	return (wx_plane_line_in);
}
