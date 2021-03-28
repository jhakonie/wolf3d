/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse_obj_uv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:31:16 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 14:54:19 by ***REMOVED***         ###   ########.fr       */
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

t_bool	wc_parse_obj_uv(t_parse_context *pc, t_p2s *p2s)
{
	t_c8 const	*b;
	t_u64		i;
	t_p2		p2;

	b = pc->p;
	if (!wc_parse_keyword(pc, "vt"))
		return (zz_on_error(pc, b));
	i = 0;
	while (i < 2)
	{
		wc_parse_whitespace(pc);
		if (!wc_parse_f32(pc, &p2.x + i))
			return (zz_on_error(pc, b));
		++i;
	}
	if (!wc_p2s_add_back(p2s, &p2))
		return (zz_on_error(pc, b));
	return (wx_true);
}
