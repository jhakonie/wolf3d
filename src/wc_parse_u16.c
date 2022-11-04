/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse_u16.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:45:24 by name          #+#    #+#             */
/*   Updated: 2021/04/12 22:01:45 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_parse.h"

/*
** exampple: 01234
*/

/*
** 2021-03-07 todo: what to do about leading 0s?
*/

t_bool	wc_parse_u16(t_parse_context *pc, t_u16 *n)
{
	char const	*b;
	t_u16		integer;

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
