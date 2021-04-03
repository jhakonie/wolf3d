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
** 2021-04-02 todo: the whole damn thing. for now just plot a point for each
** vertex
*/
static void	zz_draw(t_draw_context *dc)
{
	t_face	face;
	t_u64	i;
	t_u64	j;
	t_p3	*p;

	i = 0;
	while (i < dc->buffers->visible_indices_size)
	{
		face = (t_face){{dc->buffers->visible_indices[i + 0],
			dc->buffers->visible_indices[i + 1],
			dc->buffers->visible_indices[i + 2]}};
		j = 0;
		while (j < 3)
		{
			p = dc->buffers->screen_positions + face.indices[j];
			if (p->x >= 0.0f && p->x < dc->frame_buffer->width
				&& p->y >= 0.0f && p->y <= dc->frame_buffer->height)
				wc_draw_pixel(dc->frame_buffer, p->x, p->y, 0xff0000ff);
			++j;
		}
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
** 2021-04-03 todo: dc->buffers->sreen_positions oob check
*/
static void	zz_screen_from_view(t_draw_context *dc)
{
	t_p4	clip;
	t_u64	i;
	t_f32	k;
	t_p3	ndc;

	i = 0;
	while (i < dc->buffers->view_positions_size)
	{
		clip = wx_m44_mul_p3_f32(&dc->clip_from_view,
				dc->buffers->view_positions + i, 1.0f);
		k = 1.0f / clip.w;
		ndc = (t_p3){k * clip.x, k * clip.y, k * clip.z};
		dc->buffers->screen_positions[i] = (t_p3){(-ndc.x + 1.0f)
			* (0.5 * dc->frame_buffer->width), (-ndc.y + 1.0f)
			* (0.5 * dc->frame_buffer->height), ndc.z};
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
** - screen positions
*/
void	wc_draw_mesh(t_draw_context *dc, t_mesh const *m)
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
	zz_draw(dc);
}
