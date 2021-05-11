/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw_mesh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 09:27:38 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/04/02 09:27:38 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"

static void	zz_clip(t_draw_context *dc, t_mesh const *m)
{
	t_face	face;
	t_u64	i;

	i = 0;
	while (i < m->indices.size)
	{
		face = (t_face){{m->indices.buffer[i + 0], m->indices.buffer[i + 1],
			m->indices.buffer[i + 2]}};
		wc_draw_clip(dc, &face, dc->frustum.planes + 4);
		i += 3;
	}
}

/*
** 2021-05-05 todo: this could be a chance to catch degenerate triangles with
** zero area. don't know if such triangles cause problems later on in the
** pipeline. investigate
*/
static void	zz_draw(t_draw_context *dc, t_texture const *t)
{
	t_draw_face_context	dfc;
	t_u64				i;

	dfc = wc_draw_face_context_new(dc, t);
	i = 0;
	while (i < dc->buffers->visible_indices_size)
	{
		wc_draw_face_context_reset(&dfc, dc->buffers->visible_indices[i + 0],
			dc->buffers->visible_indices[i + 1],
			dc->buffers->visible_indices[i + 2]);
		wc_draw_face(&dfc);
		i += 3;
	}
}

/*
** 2021-04-02 todo: dc->buffers->view_positions oob check
*/
static void	zz_view_from_model(t_draw_context *dc, t_mesh const *m)
{
	t_u64	i;

	i = 0;
	while (i < m->vertices.size)
	{
		dc->buffers->uvs[i] = m->vertices.buffer[i].uv;
		++dc->buffers->uvs_size;
		dc->buffers->view_positions[i]
			= wx_m44_mul_p3(&dc->view_from_object,
				&m->vertices.buffer[i].position);
		++dc->buffers->view_positions_size;
		++i;
	}
}

/*
** 2021-04-03 note: the coordinate systems possibly look as follows:
** ndc:            screen, pseudo-2d/3d still has depth:
**      y               +--------->x
**      ^              /|
**      |             / |
**      |            /  |
** -----+---->x     /   |
**     /|          z    |
**    / |               v
**   z  |               y
**
**
** 2021-04-03 todo: figure out the whole -ndc.x business when going from ndc to
** screen space. it would indicate i've misunderstod something. stupid math.
** world would be a better place with out it
**
** perhaps it's because view space is right-handed with camera looking towards
** +z, so that's still true for clip space(?) and then above picture of ndc is
** wrong?
**
** 2021-04-21 todo: decide what to do with screen_position.z? for now
** sreen_position.z = 1.0f/view_z. currently we're not doing anything with ndc.z
** either. so what's that about? ndc.z is mapped [near = 1.0f, far = 0.0f]
*/
static void	zz_screen_from_view(t_draw_context *dc)
{
	t_p4	clip;
	t_u64	i;
	t_f32	inv_view_z;
	t_p3	ndc;

	i = 0;
	while (i < dc->buffers->view_positions_size)
	{
		clip = wx_m44_mul_p3_f32(&dc->clip_from_view,
				dc->buffers->view_positions + i, 1.0f);
		inv_view_z = 1.0f / clip.w;
		ndc = (t_p3){inv_view_z * clip.x, inv_view_z * clip.y,
			inv_view_z * clip.z};
		dc->buffers->screen_positions[i] = (t_p3){(-ndc.x + 1.0f)
			* (0.5 * dc->frame_buffer->width), (-ndc.y + 1.0f)
			* (0.5 * dc->frame_buffer->height), inv_view_z};
		++dc->buffers->screen_positions_size;
		++i;
	}
}

/*
** 2021-04-01 note: clips polygon against near plane only. the other frustum
** planes are taken care of when rasterizing the face and its screen-space
** bounding box is clipped to the frame buffer
**
** 2021-04-02 todo:
** - some kind of sanity checks so we don't run out of bounds on dc->vertices
** and dc->visible_indices
** - calculate per-pipeline_vertex clip state against the frustum:
** f (cs & wx_frustum_aabb_near)
** {
**     if (pv->view_position.z < dc->frustum.planes[4].d)
**     {
**         // todo: set per-pipeline-vertex clip state
**     }
** }
** - reject faces which are completely outside the clip planes based on above
** - accept faces which are completely inside the clip planes based on above
** - reject faces facing away from the camera
** - normals and lighting
** - uvs
*/
void	wc_draw_mesh(t_draw_context *dc, t_mesh const *m, t_texture const *t)
{
	t_frustum_aabb		cs;

	cs = wx_frustum_aabb_test(&dc->frustum, &m->aabb, &dc->view_from_object);
	if (cs == wx_frustum_aabb_all_out)
	{
		return ;
	}
	zz_view_from_model(dc, m);
	zz_clip(dc, m);
	zz_screen_from_view(dc);
	zz_draw(dc, t);
}
