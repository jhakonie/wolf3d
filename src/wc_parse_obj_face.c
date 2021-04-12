/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse_obj_face.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:48:48 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/04/12 22:26:00 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"
#include "wx_parse.h"

static t_bool	zz_parse_vertex_indices(t_parse_context *pc,
	t_obj_vertices *ovs)
{
	t_u16			i;
	t_obj_vertex	ov;

	ov.out_index = -1;
	if (!wc_parse_u16(pc, &i))
		return (wx_false);
	ov.position = i - 1;
	if (!wx_parse_keyword(pc, "/"))
		return (wx_false);
	if (!wc_parse_u16(pc, &i))
		return (wx_false);
	ov.uv = i - 1;
	if (!wx_parse_keyword(pc, "/"))
		return (wx_false);
	if (!wc_parse_u16(pc, &i))
		return (wx_false);
	ov.normal = i - 1;
	if (!wc_obj_vertices_add_back(ovs, &ov))
		return (wx_false);
	return (wx_true);
}

static t_bool	zz_on_error(t_parse_context *pc, t_c8 const *b)
{
	pc->p = b;
	return (wx_false);
}

t_bool	wc_parse_obj_face(t_parse_context *pc, t_obj_vertices *ovs)
{
	t_c8 const	*b;
	t_u8		i;

	b = pc->p;
	if (!wx_parse_keyword(pc, "f"))
	{
		return (zz_on_error(pc, b));
	}
	i = 0;
	while (i < 3)
	{
		wx_parse_whitespace(pc);
		if (!zz_parse_vertex_indices(pc, ovs))
		{
			return (zz_on_error(pc, b));
		}
		++i;
	}
	return (wx_true);
}
