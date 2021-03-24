/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 10:04:10 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 14:54:49 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_parse.h"

static t_bool	zz_is_whitespace(char c)
{
	if (c != ' ' && c != '\f' && c != '\n' && c != '\r' && c != '\t'
		&& c != '\t')
	{
		return (wx_false);
	}
	return (wx_true);
}

/*
** example:
*/

t_bool	wc_parse_whitespace(t_parse_context *pc)
{
	char const	*b;

	b = pc->p;
	while (pc->p < pc->e && zz_is_whitespace(*pc->p))
	{
		++pc->p;
	}
	if (pc->p == b)
	{
		return (wx_false);
	}
	return (wx_true);
}
