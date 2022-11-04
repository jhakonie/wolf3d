/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_mesh_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 22:02:38 by name          #+#    #+#             */
/*   Updated: 2021/04/12 22:31:11 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"
#include "wc_parse.h"
#include "wx_parse.h"

static t_bool	zz_on_error(t_c8s *fb, t_mesh *m, t_u8 i)
{
	if (i > 2)
	{
		wc_vertices_del(&m->vertices);
	}
	if (i > 1)
	{
		wc_u16s_del(&m->indices);
	}
	if (i > 0)
	{
		wx_c8s_del(fb);
	}
	return (wx_false);
}

t_bool	wc_mesh_new_from_file(t_mesh *m, char const *filename)
{
	t_c8s			fb;
	t_parse_context	pc;

	if (!wx_c8s_new_from_file(&fb, 1024, filename))
		return (zz_on_error(&fb, m, 0));
	if (!wc_u16s_new(&m->indices, 1024))
		return (zz_on_error(&fb, m, 1));
	if (!wc_vertices_new(&m->vertices, 1024))
		return (zz_on_error(&fb, m, 2));
	pc.p = (char const *)fb.buffer;
	pc.e = (char const *)(fb.buffer + fb.size);
	if (!wc_parse_obj(&pc, m, wx_true))
	{
		return (zz_on_error(&fb, m, 3));
	}
	wx_c8s_del(&fb);
	wc_mesh_aabb(m);
	return (wx_true);
}
