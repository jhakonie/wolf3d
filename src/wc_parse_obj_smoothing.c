/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse_obj_smoothing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:43:32 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/07 19:02:58 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_parse.h"

/*
** 2021-03-07 todo: find out what this is and implement it properly
*/

t_bool	wc_parse_obj_smoothing(t_parse_context *pc)
{
	if (!wc_parse_keyword(pc, "s"))
	{
		return (wx_false);
	}
	if (!wc_parse_whitespace(pc))
	{
		return (wx_false);
	}
	while (pc->p < pc->e)
	{
		if (*(t_s8 *)pc->p == '\n')
		{
			++pc->p;
			break ;
		}
		++pc->p;
	}
	return (wx_true);
}
