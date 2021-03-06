/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_q4_new_v3_f32.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:13:02 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/04 11:15:36 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

#include "wx_math.h"

t_q4	wx_q4_new_v3_f32(t_v3 const *axis, t_f32 rad)
{
	t_q4	q;
	t_f32	sin2;

	sin2 = sinf(0.5f * rad);
	q.x = sin2 * axis->x;
	q.y = sin2 * axis->y;
	q.z = sin2 * axis->z;
	q.w = cosf(0.5f * rad);
	return (q);
}
