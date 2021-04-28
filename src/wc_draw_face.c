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

#include "wc_draw.h"

/*
** 2021-04-08 todo: clamping to [0.0f, width] and [0.0f, height] introduces
** some inaccuracy? does there need to be some sort of +/-0.5f offsets?
**
** 2021-04-26 todo: really need to think how to properly be pixel-accurate here.
** the vertex coordinates will not usually hit pixel centers
*/
static t_rectangle	zz_screen_aabb2(t_p3 const *p0, t_p3 const *p1,
	t_p3 const *p2, t_frame_buffer const *fb)
{
	t_rectangle	r;

	r.p0.x = wx_f32_max(0.0f, wx_f32_min(wx_f32_min(p0->x, p1->x), p2->x));
	r.p0.y = wx_f32_max(0.0f, wx_f32_min(wx_f32_min(p0->y, p1->y), p2->y));
	r.p1.x = wx_f32_min(wx_f32_max(wx_f32_max(p0->x, p1->x), p2->x),
			fb->width);
	r.p1.y = wx_f32_min(wx_f32_max(wx_f32_max(p0->y, p1->y), p2->y),
			fb->height);
	return (r);
}

/*
** 2021-04-09 note:
** the "2d" area in screen space of the projected face
** screen, pseudo-2d/3d omitting z-axis:
** +------------>x
** |   p0       p2
** |    +-------+
** |     \     /
** |      \   /
** |       \ /
** |        +
** v        p1
** y
*/
static t_f32	zz_screen_area(t_p3 const *p0, t_p3 const *p1, t_p3 const *p2)
{
	t_f32	a;

	a = 0.5f * ((p1->y - p0->y) * (p2->x - p0->x) - (p1->x - p0->x)
			* (p2->y - p0->y));
	return (a);
}

/*
** 2021-04-10 todo: top-left filling rule
** static t_bool	zz_edge_top_or_left_test(t_p3 const *p0, t_p3 const *p1)
** {
**	if (p0->x > p1->x && p0->y == p1->y)
**	{
**		return (wx_true);
**	}
**	if (p0->y > p1->y)
**	{
**		return (wx_true);
**	}
**	return (wx_false);
** }
*/

/*
** 2021-04-26 note: a "2d" edge function in screen space looks like:
** screen, pseudo-2d/3d omitting z-axis:
** +------------>x
** |        p0
** |         +
** |          \  (+ side)
** |           \    +p
** | (- side)   \
** |             +
** v             p1
** y
**     (p1->y - p0->y) * (p->x - p0->x) - (p1->x - p0->x) * (p->y - p0->y)
**
** shuffling it:
**     (p1->y - p0->y) * p->x + (p1->x + p0->x) * p->y +
**     (p1->x * p0->y - p1->y * p0->x)
**
** shows the x: (p1->y - p0->y), and y: (p1->x + p0->x) gradients
**
** from there for each edge the x- and y-steps for the face's u, v and w:
** u x_step = (p1->y - p0->y)
** u y_step = (p1->x + p0->x)
** v x_step = (p2->y - p1->y)
** v y_step = (p2->x + p1->x)
** w x_step = (p0->y - p2->y)
** w y_step = (p0->x + p2->x)
**
** which could lead to a faster way to update u, v, w for a per pixel
** rather than calling zz_screen_area() three times per pixel
*/
static t_draw_face_context	zz_draw_face_context_new(t_draw_context *dc,
	t_p3 const *p0, t_p3 const *p1, t_p3 const *p2)
{
	t_draw_face_context	dfc;

	dfc.fb = dc->frame_buffer;
	dfc.db = dc->depth_buffer;
	dfc.p0 = p0;
	dfc.p1 = p1;
	dfc.p2 = p2;
	dfc.aabb = zz_screen_aabb2(p0, p1, p2, dc->frame_buffer);
	dfc.inv_face_area = 1.0f / zz_screen_area(p0, p1, p2);
	dfc.u = 0.0f;
	dfc.v = 0.0f;
	dfc.w = 0.0f;
	return (dfc);
}

/*
** 2021-04-28 todo: think about what to store in the depth buffer. right now
** it's the interpolated 1.0f/view.z for the pixel, so smaller values are
** further away. maybe that's ok?
*/
static void	zz_draw(t_draw_face_context *dfc)
{
	dfc->u = zz_screen_area(dfc->p0, dfc->p1, &dfc->p) * dfc->inv_face_area;
	dfc->v = zz_screen_area(dfc->p1, dfc->p2, &dfc->p) * dfc->inv_face_area;
	dfc->w = zz_screen_area(dfc->p2, dfc->p0, &dfc->p) * dfc->inv_face_area;
	if (dfc->u >= 0.0f && dfc->v >= 0.0f && dfc->w >= 0.0f)
	{
		dfc->z = dfc->u * dfc->p0->z + dfc->v * dfc->p1->z + dfc->w
			* dfc->p2->z;
		if (dfc->z > wc_depth_buffer_get(dfc->db, dfc->p.x, dfc->p.y))
		{
			wx_frame_buffer_set(dfc->fb, dfc->p.x, dfc->p.y, 0xff0000ff);
			wc_depth_buffer_set(dfc->db, dfc->p.x, dfc->p.y, dfc->z);
		}
	}
}

void	wc_draw_face(t_draw_context *dc, t_p3 const *p0, t_p3 const *p1,
	t_p3 const *p2)
{
	t_draw_face_context	dfc;

	dfc = zz_draw_face_context_new(dc, p0, p1, p2);
	dfc.p.z = 0.0f;
	dfc.p.y = dfc.aabb.p0.y;
	while (dfc.p.y < dfc.aabb.p1.y)
	{
		dfc.p.x = dfc.aabb.p0.x;
		while (dfc.p.x < dfc.aabb.p1.x)
		{
			zz_draw(&dfc);
			++dfc.p.x;
		}
		++dfc.p.y;
	}
}
