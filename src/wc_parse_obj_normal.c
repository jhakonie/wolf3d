/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse_obj_normal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:37:34 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 14:51:05 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"
#include "wc_parse.h"
#include "wx_math.h"

static t_bool	zz_on_error(t_parse_context *pc, t_c8 const *b)
{
	pc->p = b;
	return (wx_false);
}

t_bool	wc_parse_obj_normal(t_parse_context *pc, t_n3s *n3s)
{
	t_c8 const	*b;
	t_u64		i;
	t_n3		n3;

	b = pc->p;
	if (!wc_parse_keyword(pc, "vn"))
		return (zz_on_error(pc, b));
	i = 0;
	while (i < 3)
	{
		wc_parse_whitespace(pc);
		if (!wc_parse_f32(pc, &n3.x + i))
			return (zz_on_error(pc, b));
		++i;
	}
	if (!wc_n3s_add_back(n3s, &n3))
		return (zz_on_error(pc, b));
	return (wx_true);
}
