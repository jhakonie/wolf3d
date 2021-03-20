/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse_face.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:48:48 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/20 06:53:26 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"
#include "wc_parse.h"

static t_bool	zz_parse_vertex_indices(t_parse_context *pc, t_face *f, t_u8 i)
{
	if (!wc_parse_u16(pc, &f->positions[i]))
	{
		return (wx_false);
	}
	if (!wc_parse_keyword(pc, "/"))
	{
		return (wx_false);
	}
	if (!wc_parse_u16(pc, &f->uvs[i]))
	{
		return (wx_false);
	}
	if (!wc_parse_keyword(pc, "/"))
	{
		return (wx_false);
	}
	if (!wc_parse_u16(pc, &f->normals[i]))
	{
		return (wx_false);
	}
	return (wx_true);
}

static t_bool	zz_on_error(t_parse_context *pc, t_s8 *b)
{
	pc->p = b;
	return (wx_false);
}

t_bool			wc_parse_face(t_parse_context *pc, t_mesh *m)
{
	t_s8	*b;
	t_u8	i;
	t_face	f;

	b = (t_s8 *)pc->p;
	if (!wc_parse_keyword(pc, "f"))
	{
		return (zz_on_error(pc, b));
	}
	i = 0;
	while (i < 3)
	{
		wc_parse_whitespace(pc);
		if (!zz_parse_vertex_indices(pc, &f, i))
		{
			return (zz_on_error(pc, b));
		}
		++i;
	}
	if (!wc_darray_add_back(&m->faces, &f))
	{
		return (zz_on_error(pc, b));
	}
	return (wx_true);
}
