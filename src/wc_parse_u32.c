/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse_u32.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 10:03:08 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/07 16:04:50 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_parse.h"

/*
** exampple: 01234
*/

/*
** 2021-03-07 todo: what to do about leading 0s?
*/

t_bool	wc_parse_u32(t_parse_context *pc, t_u32 *n)
{
	char const	*b;
	t_u32		integer;

	b = pc->p;
	*n = 0;
	integer = 0;
	while (pc->p < pc->e && *pc->p >= '0' && *pc->p <= '9')
	{
		integer = 10 * integer + (*pc->p - '0');
		++pc->p;
	}
	if (pc->p == b)
	{
		pc->p = b;
		return (wx_false);
	}
	*n = integer;
	return (wx_true);
}
