/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_plane_signed_distance_p3.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 08:23:17 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 15:54:29 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_math.h"

t_f32	wx_plane_signed_distance_p3(t_plane const *pl, t_p3 const *p)
{
	t_f32	distance;
	t_f32	dot;

	dot = p->x * pl->n.x + p->y * pl->n.y + p->z * pl->n.z;
	distance = dot + pl->d;
	return (distance);
}
