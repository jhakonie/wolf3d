/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_m44_new_inverse_q4_p3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: name <name@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:59:57 by name          #+#    #+#             */
/*   Updated: 2021/03/24 15:49:52 by name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_math.h"

static void	zz_m33_mul_p3(t_m44 *m)
{
	t_p3	p;

	p = (t_p3){m->xs[12], m->xs[13], m->xs[14]};
	m->xs[12] = m->xs[0] * p.x + m->xs[4] * p.y + m->xs[8] * p.z;
	m->xs[13] = m->xs[1] * p.x + m->xs[5] * p.y + m->xs[9] * p.z;
	m->xs[14] = m->xs[2] * p.x + m->xs[6] * p.y + m->xs[10] * p.z;
}

static void	zz_m33_transpose(t_m44 *m)
{
	t_f32	t;

	t = m->xs[1];
	m->xs[1] = m->xs[4];
	m->xs[4] = t;
	t = m->xs[2];
	m->xs[2] = m->xs[8];
	m->xs[8] = t;
	t = m->xs[6];
	m->xs[6] = m->xs[9];
	m->xs[9] = t;
}

static void	zz_p3_negate(t_m44 *m)
{
	m->xs[12] = -m->xs[12];
	m->xs[13] = -m->xs[13];
	m->xs[14] = -m->xs[14];
}

t_m44	wx_m44_new_inverse_q4_p3(t_q4 const *q, t_p3 const *p)
{
	t_m44	m;

	m = wx_m44_new_q4_p3(q, p);
	zz_m33_transpose(&m);
	zz_m33_mul_p3(&m);
	zz_p3_negate(&m);
	return (m);
}
