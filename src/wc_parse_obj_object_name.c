/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse_obj_object_name.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:23:36 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/07 18:59:57 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_parse.h"

t_bool	wc_parse_obj_object_name(t_parse_context *pc)
{
	if (!wc_parse_keyword(pc, "o"))
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
