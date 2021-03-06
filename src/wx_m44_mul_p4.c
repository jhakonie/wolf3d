/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_m44_mul_p4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:04:15 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/04 23:40:39 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_math.h"

t_p4	wx_m44_mul_p4(t_m44 const *l, t_p4 const *r)
{
	t_p4	p;

	p.x = l->xs[0] * r->x + l->xs[4] * r->y + l->xs[8] * r->z + l->xs[12];
	p.y = l->xs[1] * r->x + l->xs[5] * r->y + l->xs[9] * r->z + l->xs[13];
	p.z = l->xs[2] * r->x + l->xs[6] * r->y + l->xs[10] * r->z + l->xs[14];
	p.w = l->xs[3] * r->x + l->xs[7] * r->y + l->xs[11] * r->z + l->xs[15];
	return (p);
}
