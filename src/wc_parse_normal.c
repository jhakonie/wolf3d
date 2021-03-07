/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse_normal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:37:34 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/07 22:06:33 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"
#include "wc_parse.h"
#include "wx_math.h"

static t_bool	zz_on_error(t_parse_context *pc, t_s8 *b)
{
	pc->p = b;
	return (wx_false);
}

t_bool			wc_parse_normal(t_parse_context *pc, t_mesh *m)
{
	t_s8	*b;
	t_u64	i;
	t_n3	normal;

	b = (t_s8 *)pc->p;
	if (!wc_parse_keyword(pc, "vn"))
		return (zz_on_error(pc, b));
	i = 0;
	while (i < 3)
	{
		wc_parse_whitespace(pc);
		if (!wc_parse_f32(pc, &normal.x + i))
			return (zz_on_error(pc, b));
		++i;
	}
	if (!wc_darray_add_back(&m->normals, &normal))
		return (zz_on_error(pc, b));
	return (wx_true);
}
