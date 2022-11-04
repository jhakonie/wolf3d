/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_m44_new_q4_p3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: name <name@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:25:11 by name          #+#    #+#             */
/*   Updated: 2021/03/04 11:05:33 by name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_math.h"

/*
** 2021-05-29 note: the current [0], [5] and [10] should be equivalent to:
** m.xs[0] = (2.0f * q->x * q->x + 2.0f * q->w * q->w) - 1.0f;
** m.xs[5] = (2.0f * q->y * q->y + 2.0f * q->w * q->w) - 1.0f;
** m.xs[10] = (2.0f * q->z * q->z + 2.0f * q->w * q->w) - 1.0f;
** that is shown in some literature
*/
t_m44	wx_m44_new_q4_p3(t_q4 const *q, t_p3 const *p)
{
	t_m44	m;

	m.xs[0] = 1.0f - 2.0f * q->y * q->y - 2.0f * q->z * q->z;
	m.xs[1] = 2.0f * q->x * q->y + 2.0f * q->z * q->w;
	m.xs[2] = 2.0f * q->x * q->z - 2.0f * q->y * q->w;
	m.xs[3] = 0.0f;
	m.xs[4] = 2.0f * q->x * q->y - 2.0f * q->z * q->w;
	m.xs[5] = 1.0f - 2.0f * q->x * q->x - 2.0f * q->z * q->z;
	m.xs[6] = 2.0f * q->y * q->z + 2.0f * q->x * q->w;
	m.xs[7] = 0.0f;
	m.xs[8] = 2.0f * q->x * q->z + 2.0f * q->y * q->w;
	m.xs[9] = 2.0f * q->y * q->z - 2.0f * q->x * q->w;
	m.xs[10] = 1.0f - 2.0f * q->x * q->x - 2.0f * q->y * q->y;
	m.xs[11] = 0.0f;
	m.xs[12] = p->x;
	m.xs[13] = p->y;
	m.xs[14] = p->z;
	m.xs[15] = 1.0f;
	return (m);
}
