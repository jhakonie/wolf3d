/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse_obj_uv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:31:16 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/04/12 22:26:00 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"
#include "wc_parse.h"
#include "wx_math.h"
#include "wx_parse.h"

static t_bool	zz_on_error(t_parse_context *pc, t_c8 const *b)
{
	pc->p = b;
	return (wx_false);
}

/*
** 2021-05-22 todo: blender seems to export uv in such way that bottom-left is
** [0,0] and top-right is [1,1]. i guess we want to invert the v-axis so that
** top-left is [0, 0] and bottom-right is [1, 1]. needs to agree with
** wc_texture_get(). right now it does not
*/
t_bool	wc_parse_obj_uv(t_parse_context *pc, t_p2s *p2s, t_bool inv_v)
{
	t_c8 const	*b;
	t_u64		i;
	t_p2		p2;

	b = pc->p;
	if (!wx_parse_keyword(pc, "vt"))
		return (zz_on_error(pc, b));
	i = 0;
	while (i < 2)
	{
		wx_parse_whitespace(pc);
		if (!wx_parse_f32(pc, &p2.x + i))
			return (zz_on_error(pc, b));
		++i;
	}
	if (inv_v)
	{
		p2.y = 1.0 - p2.y;
	}
	if (!wc_p2s_add_back(p2s, &p2))
		return (zz_on_error(pc, b));
	return (wx_true);
}
