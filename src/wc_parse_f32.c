/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse_f32.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 10:00:13 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 14:49:56 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_parse.h"

static t_bool	zz_parse_f32_fractional(t_parse_context *pc, t_f32 *n)
{
	char const	*b;
	t_u32		divisor;
	t_u32		fractional;

	b = pc->p;
	*n = 0.0f;
	divisor = 1;
	fractional = 0;
	while (pc->p < pc->e && *pc->p >= '0' && *pc->p <= '9')
	{
		fractional = 10 * fractional + (*pc->p - '0');
		divisor = 10 * divisor;
		++pc->p;
	}
	if (pc->p == b)
	{
		return (wx_false);
	}
	*n = (t_f32)fractional / (t_f32)divisor;
	return (wx_true);
}

/*
** 2021-03-07 todo: what to do about leading 0s?
*/

static t_bool	zz_parse_f32_sign_integer(t_parse_context *pc, t_f32 *s,
	t_f32 *n)
{
	char const	*b;
	t_u32		integer;

	b = pc->p;
	*n = 0.0f;
	*s = 1.0f;
	if (pc->p < pc->e && *pc->p == '-')
	{
		++pc->p;
		*s = -1.0f;
	}
	integer = 0;
	while (pc->p < pc->e && *pc->p >= '0' && *pc->p <= '9')
	{
		integer = 10 * integer + (*pc->p - '0');
		++pc->p;
	}
	if (pc->p == b || (pc->p == (b + 1) && *s < 0))
	{
		pc->p = b;
		return (wx_false);
	}
	*n = (t_f32)integer;
	return (wx_true);
}

/*
** example: -3.14159
*/

/*
** 2021-03-07 todo: figure out a way to do this which adheres to numeric limits
** and behaves "accurately" with integer or fractional parts which cannot be
** exactly represented by floating point numbers
*/

t_bool	wc_parse_f32(t_parse_context *pc, t_f32 *n)
{
	t_f32	fractional;
	t_f32	integer;
	t_f32	sign;

	*n = 0.0f;
	if (!zz_parse_f32_sign_integer(pc, &sign, &integer))
	{
		return (wx_false);
	}
	fractional = 0.0f;
	if (pc->p < pc->e && *pc->p == '.')
	{
		++pc->p;
		zz_parse_f32_fractional(pc, &fractional);
	}
	*n = sign * (integer + fractional);
	return (wx_true);
}
