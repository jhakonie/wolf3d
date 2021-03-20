/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_mesh_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 22:02:38 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/20 07:39:13 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"
#include "wc_parse.h"

static void		zz_aabb(t_mesh *m)
{
	t_u64		i;
	t_p3 const	*ps;
	t_u64		ps_size;

	m->aabb.max = (t_p3){-WX_F32_INF, -WX_F32_INF, -WX_F32_INF};
	m->aabb.min = (t_p3){WX_F32_INF, WX_F32_INF, WX_F32_INF};
	ps = (t_p3 const *)m->positions.buffer;
	ps_size = m->positions.size / m->positions.element_size;
	i = 0;
	while (i < ps_size)
	{
		m->aabb.max.x = wx_f32_max(ps[i].x, m->aabb.max.x);
		m->aabb.max.y = wx_f32_max(ps[i].y, m->aabb.max.y);
		m->aabb.max.z = wx_f32_max(ps[i].z, m->aabb.max.z);
		m->aabb.min.x = wx_f32_min(ps[i].x, m->aabb.min.x);
		m->aabb.min.y = wx_f32_min(ps[i].y, m->aabb.min.y);
		m->aabb.min.z = wx_f32_min(ps[i].z, m->aabb.min.z);
		++i;
	}
}

static t_bool	zz_parse_mesh(t_parse_context *pc, t_mesh *m)
{
	while (pc->p < pc->e)
	{
		if (!wc_parse_whitespace(pc) && !wc_parse_comment(pc) &&
			!wc_parse_position(pc, m) && !wc_parse_material_filename(pc) &&
			!wc_parse_object_name(pc) && !wc_parse_uv(pc, m) &&
			!wc_parse_normal(pc, m) && !wc_parse_material_name(pc) &&
			!wc_parse_smoothing(pc) && !wc_parse_face(pc, m))
		{
			break ;
		}
	}
	if (pc->p != pc->e)
	{
		return (wx_false);
	}
	return (wx_true);
}

static t_bool	zz_on_error(t_darray *fb, t_mesh *m, t_u8 i)
{
	if (i > 4)
	{
		wc_darray_del(&m->uvs);
	}
	if (i > 3)
	{
		wc_darray_del(&m->positions);
	}
	if (i > 2)
	{
		wc_darray_del(&m->normals);
	}
	if (i > 1)
	{
		wc_darray_del(&m->faces);
	}
	if (i > 0)
	{
		wc_darray_del(fb);
	}
	return (wx_false);
}

t_bool			wc_mesh_new(t_mesh *m, char const *filename)
{
	t_darray		fb;
	t_parse_context	pc;

	if (!wc_darray_new_file(&fb, filename, 1))
		return (zz_on_error(&fb, m, 0));
	if (!wc_darray_new(&m->faces, 0, sizeof(t_face)))
		return (zz_on_error(&fb, m, 1));
	if (!wc_darray_new(&m->normals, 0, sizeof(t_n3)))
		return (zz_on_error(&fb, m, 2));
	if (!wc_darray_new(&m->positions, 0, sizeof(t_v3)))
		return (zz_on_error(&fb, m, 3));
	if (!wc_darray_new(&m->uvs, 0, sizeof(t_p2)))
		return (zz_on_error(&fb, m, 4));
	pc.p = (char const *)fb.buffer;
	pc.e = (char const *)(fb.buffer + fb.size);
	if (!zz_parse_mesh(&pc, m))
	{
		return (zz_on_error(&fb, m, 5));
	}
	wc_darray_del(&fb);
	zz_aabb(m);
	return (wx_true);
}
