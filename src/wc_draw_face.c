/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw_face.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 11:34:16 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/04/05 11:34:16 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

#include "wc_draw.h"

/*
** 2021-04-10 todo: top-left filling rule
**
**
** 2021-04-28 todo: think about what to store in the depth buffer. right now
** it's the interpolated 1.0f/view.z for the pixel, so smaller values are
** further away. maybe that's ok?
*/
static void	zz_draw(t_draw_face_context *dfc)
{
	t_u32	c;

	c = wc_texture_get(dfc->t, dfc->texture_u, dfc->texture_v);
	wx_frame_buffer_set(dfc->fb, dfc->p.x, dfc->p.y, c);
	wc_depth_buffer_set(dfc->db, dfc->p.x, dfc->p.y, dfc->p_inv_view_z);
}

/* 2021-05-09 todo: this is the most basic straight line translation of the math
** and does not take advantage of any affine properties. meaning that it ends up
** calling wc_screen_xy_area() too many times and otherwise doing other
** calculations when not strictly necessary
**
** look into implementing the same functionality by precomputing any constants
** per face, which would then make per pixel cost lower hopefully
**
** 2021-06-01 todo: texture uv coordinates still go outside of [0.0f, 1.0f]. as
** crap fix could just clamp them
*/
static t_bool	zz_interpolate(t_draw_face_context *dfc)
{
	dfc->screen_a0 = wc_screen_xy_area(dfc->screen_p1, dfc->screen_p2, &dfc->p);
	dfc->screen_a1 = wc_screen_xy_area(dfc->screen_p2, dfc->screen_p0, &dfc->p);
	dfc->screen_a2 = wc_screen_xy_area(dfc->screen_p0, dfc->screen_p1, &dfc->p);
	if (dfc->screen_a0 < 0.0f || dfc->screen_a1 < 0.0f || dfc->screen_a2 < 0.0f)
	{
		return (wx_false);
	}
	dfc->p_inv_view_z = dfc->screen_a0 * dfc->screen_p0->z + dfc->screen_a1
		* dfc->screen_p1->z + dfc->screen_a2 * dfc->screen_p2->z;
	if (dfc->p_inv_view_z < wc_depth_buffer_get(dfc->db, dfc->p.x, dfc->p.y))
	{
		return (wx_false);
	}
	dfc->inv_a = 1.0f / ((dfc->view_z1 * dfc->view_z2 * dfc->screen_a0)
			+ (dfc->view_z2 * dfc->view_z0 * dfc->screen_a1) + (dfc->view_z0
				* dfc->view_z1 * dfc->screen_a2));
	dfc->view_b0 = (dfc->view_z1 * dfc->view_z2 * dfc->screen_a0) * dfc->inv_a;
	dfc->view_b1 = (dfc->view_z2 * dfc->view_z0 * dfc->screen_a1) * dfc->inv_a;
	dfc->view_b2 = (dfc->view_z0 * dfc->view_z1 * dfc->screen_a2) * dfc->inv_a;
	dfc->texture_u = dfc->view_b0 * dfc->uv0->x + dfc->view_b1 * dfc->uv1->x
		+ dfc->view_b2 * dfc->uv2->x;
	dfc->texture_v = dfc->view_b0 * dfc->uv0->y + dfc->view_b1 * dfc->uv1->y
		+ dfc->view_b2 * dfc->uv2->y;
	return (wx_true);
}

/*
** 2021-06-01 todo: ceilf() calls should be in somewhere else where they are
** done only once per face
*/
void	wc_draw_face(t_draw_face_context *dfc)
{
	dfc->p.y = ceilf(dfc->aabb.p0.y - 0.5f);
	while (dfc->p.y < dfc->aabb.p1.y)
	{
		dfc->p.x = ceilf(dfc->aabb.p0.x - 0.5f);
		while (dfc->p.x < dfc->aabb.p1.x)
		{
			if (zz_interpolate(dfc))
			{
				zz_draw(dfc);
			}
			++dfc->p.x;
		}
		++dfc->p.y;
	}
}
