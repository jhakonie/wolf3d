/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_mesh_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 22:02:38 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/04/12 22:31:11 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"
#include "wc_parse.h"
#include "wx_parse.h"

static void	zz_aabb(t_mesh *m)
{
	t_u64		i;

	m->aabb.max = (t_p3){-WX_F32_INF, -WX_F32_INF, -WX_F32_INF};
	m->aabb.min = (t_p3){WX_F32_INF, WX_F32_INF, WX_F32_INF};
	i = 0;
	while (i < m->vertices.size)
	{
		m->aabb.max.x = wx_f32_max(m->vertices.buffer[i].position.x,
				m->aabb.max.x);
		m->aabb.max.y = wx_f32_max(m->vertices.buffer[i].position.y,
				m->aabb.max.y);
		m->aabb.max.z = wx_f32_max(m->vertices.buffer[i].position.z,
				m->aabb.max.z);
		m->aabb.min.x = wx_f32_min(m->vertices.buffer[i].position.x,
				m->aabb.min.x);
		m->aabb.min.y = wx_f32_min(m->vertices.buffer[i].position.y,
				m->aabb.min.y);
		m->aabb.min.z = wx_f32_min(m->vertices.buffer[i].position.z,
				m->aabb.min.z);
		++i;
	}
}

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

t_bool	wc_mesh_new(t_mesh *m, char const *filename)
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
	if (!wc_parse_obj(&pc, m))
	{
		return (zz_on_error(&fb, m, 3));
	}
	wx_c8s_del(&fb);
	zz_aabb(m);
	return (wx_true);
}
