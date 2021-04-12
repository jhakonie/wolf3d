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
*/
static t_rectangle	zz_aabb2(t_p3 const *p0, t_p3 const *p1,
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
** 2021-04-10  todo: top-left filling rule
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
** 2021-04-09 note:
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
*/
static t_f32	zz_edge_p2_test(t_p3 const *p0, t_p3 const *p1, t_p2 const *p)
{
	t_f32	a;

	a = (p1->y - p0->y) * (p->x - p0->x) - (p1->x - p0->x) * (p->y - p0->y);
	return (a);
}

static t_bool	zz_face_p2_test(t_p3 const *p0, t_p3 const *p1, t_p3 const *p2,
	t_p2 p)
{
	t_f32	as[3];

	as[0] = zz_edge_p2_test(p1, p2, &p);
	as[1] = zz_edge_p2_test(p2, p0, &p);
	as[2] = zz_edge_p2_test(p0, p1, &p);
	if (as[0] < 0.0f || as[1] < 0.0f || as[2] < 0.0f)
	{
		return (wx_false);
	}
	return (wx_true);
}

void	wc_draw_face(t_draw_context *dc, t_p3 const *p0, t_p3 const *p1,
	t_p3 const *p2)
{
	t_rectangle	aabb;
	t_f32		x;
	t_f32		y;

	aabb = zz_aabb2(p0, p1, p2, dc->frame_buffer);
	y = aabb.p0.y;
	while (y < aabb.p1.y)
	{
		x = aabb.p0.x;
		while (x < aabb.p1.x)
		{
			if (!zz_face_p2_test(p0, p1, p2, (t_p2){x, y}))
			{
				++x;
				continue ;
			}
			wc_draw_pixel(dc->frame_buffer, x, y, 0xff0000ff);
			++x;
		}
		++y;
	}
}
