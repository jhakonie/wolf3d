/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw_clip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 01:21:09 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/04/02 01:21:09 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"

static t_p3	zz_p3_lerp(t_p3 const *p0, t_p3 const *p1, t_f32 t)
{
	t_p3	p;

	p.x = p0->x + t * (p1->x - p0->x);
	p.y = p0->y + t * (p1->y - p0->y);
	p.z = p0->z + t * (p1->z - p0->z);
	return (p);
}

static void	zz_clip_going_in(t_pipeline_buffers *pb, t_clip_context *cc)
{
	pb->view_positions[pb->view_positions_size] = zz_p3_lerp(pb->view_positions
			+ cc->i0, pb->view_positions + cc->i1, cc->t);
	cc->out_indices[cc->out_indices_size] = pb->view_positions_size;
	++pb->view_positions_size;
	++cc->out_indices_size;
	cc->out_indices[cc->out_indices_size] = cc->i1;
	++cc->out_indices_size;
	cc->i0 = cc->i1;
}

static void	zz_clip_going_out(t_pipeline_buffers *pb, t_clip_context *cc)
{
	pb->view_positions[pb->view_positions_size] = zz_p3_lerp(pb->view_positions
			+ cc->i0, pb->view_positions + cc->i1, cc->t);
	cc->out_indices[cc->out_indices_size] = pb->view_positions_size;
	++pb->view_positions_size;
	++cc->out_indices_size;
	cc->i0 = cc->i1;
}

static void	zz_clip_in(t_clip_context *cc)
{
	cc->out_indices[cc->out_indices_size] = cc->i1;
	++cc->out_indices_size;
	cc->i0 = cc->i1;
}

void	wc_draw_clip(t_draw_context *dc, t_face const *f, t_plane const *p)
{
	t_clip_context	cc;
	t_u64			i;

	cc.out_indices_size = 0;
	cc.i0 = f->indices[2];
	i = 0;
	while (i < 3)
	{
		cc.i1 = f->indices[i];
		cc.cs = wx_plane_line_test(p, dc->buffers->view_positions + cc.i0,
				dc->buffers->view_positions + cc.i1, &cc.t);
		if (cc.cs == wx_plane_line_out)
			cc.i0 = cc.i1;
		else if (cc.cs == wx_plane_line_going_in)
			zz_clip_going_in(dc->buffers, &cc);
		else if (cc.cs == wx_plane_line_going_out)
			zz_clip_going_out(dc->buffers, &cc);
		else
			zz_clip_in(&cc);
		++i;
	}
	wc_draw_add_visible(dc, &cc);
}
