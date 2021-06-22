/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:25:12 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/04/12 22:06:49 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_parse.h"
#include "wx_parse.h"

static t_bool	zz_cache_find(t_obj_vertices *c, t_obj_vertex const *v,
	t_u16 *out_i)
{
	t_u64			i;

	i = 0;
	while (i < c->size)
	{
		if (c->buffer[i].normal == v->normal
			&& c->buffer[i].position == v->position
			&& c->buffer[i].uv == v->uv)
		{
			*out_i = c->buffer[i].out_index;
			return (wx_true);
		}
		++i;
	}
	*out_i = -1;
	return (wx_false);
}

static t_bool	zz_cache_update(t_obj_vertices *c, t_parse_obj_context *poc,
	t_mesh *m, t_obj_vertex *obj_v)
{
	t_vertex		v;

	if (zz_cache_find(c, obj_v, &obj_v->out_index))
	{
		if (!wc_u16s_add_back(&m->indices, obj_v->out_index))
		{
			return (wx_false);
		}
	}
	else
	{
		obj_v->out_index = m->vertices.size;
		v = (t_vertex){poc->positions.buffer[obj_v->position],
			poc->normals.buffer[obj_v->normal], poc->uvs.buffer[obj_v->uv]};
		if (!(wc_obj_vertices_add_back(c, obj_v)
				&& wc_vertices_add_back(&m->vertices, &v)
				&& wc_u16s_add_back(&m->indices, obj_v->out_index)))
		{
			return (wx_false);
		}
	}
	return (wx_true);
}

/*
** 2021-03-27 note: obj format really has an index buffer per vertex attribute
** buffer. this function flattens that into a single index buffer. which means
** that the resulting vertex buffer has a corresponding vertex for every
** unique combination of the position-uv-normal indices
**
** this means that if two vertices share position and normal, but have different
** uv, that the position and normal attributes will be effectively duplicated
**
** this format resembless that of commonly used with opengl for example
**
** 2021-03-27 todo: implement a hash table as the vertex cache. this one is
** bound to be dead slow as soon as there are more than a handful of vertices.
** the repeated calls to zz_cache_find() looks awfully O(n^2)-ish
*/
static t_bool	zz_mesh(t_mesh *m, t_parse_obj_context *poc)
{
	t_obj_vertices	cache;
	t_u64			i;
	t_obj_vertex	*obj_v;

	if (!wc_obj_vertices_new(&cache, 1024))
		return (wx_false);
	i = 0;
	while (i < poc->vertices.size)
	{
		obj_v = poc->vertices.buffer + i;
		if (!zz_cache_update(&cache, poc, m, obj_v))
		{
			wc_obj_vertices_del(&cache);
			return (wx_false);
		}
		++i;
	}
	wc_obj_vertices_del(&cache);
	return (wx_true);
}

/*
** 2021-04-02 todo: sanity check the amount of normals, positions, uvs and
** vertices contains
**
** 2021-06-22 note: blender .obj export has uv at lower-left corner
*/
t_bool	wc_parse_obj(t_parse_context *pc, t_mesh *m, t_bool inv_v)
{
	t_parse_obj_context	poc;

	if (!wc_parse_obj_context_new(&poc))
	{
		return (wx_false);
	}
	while (pc->p < pc->e)
	{
		if (!wc_parse_obj_comment(pc) && !wc_parse_obj_face(pc, &poc.vertices)
			&& !wc_parse_obj_material_filename(pc)
			&& !wc_parse_obj_material_name(pc) && !wc_parse_obj_object_name(pc)
			&& !wc_parse_obj_normal(pc, &poc.normals)
			&& !wc_parse_obj_position(pc, &poc.positions)
			&& !wc_parse_obj_smoothing(pc) && !wc_parse_obj_uv(pc, &poc.uvs,
				inv_v) && !wx_parse_whitespace(pc))
			break ;
	}
	if (pc->p != pc->e)
	{
		wc_parse_obj_context_del(&poc);
		return (wx_false);
	}
	zz_mesh(m, &poc);
	wc_parse_obj_context_del(&poc);
	return (wx_true);
}
