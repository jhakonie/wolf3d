/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse_keyword.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 10:01:57 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/07 16:03:49 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_parse.h"

/*
** exampple: variable
*/

t_bool	wc_parse_keyword(t_parse_context *pc, char const *k)
{
	t_u64	i;

	i = 0;
	while (k[i] != '\0')
	{
		if (pc->p + i >= pc->e)
		{
			return (wx_false);
		}
		if (pc->p[i] != k[i])
		{
			return (wx_false);
		}
		++i;
	}
	pc->p = pc->p + i;
	return (wx_true);
}
