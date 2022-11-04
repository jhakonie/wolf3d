/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw_clip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: name <name@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 01:21:09 by name          #+#    #+#             */
/*   Updated: 2021/04/02 01:21:09 by name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"

/*
** 2021-05-05 note:
**
**    p0
**    +
**     \
**      \ (add new, add index)
** ------+------
**  |     \
**  |      \
**  v       + (add index)
**  n       p1
*/
static void	zz_clip_going_in(t_pipeline_buffers *pb, t_clip_context *cc)
{
	pb->uvs[pb->uvs_size] = wc_p2_lerp(pb->uvs + cc->i0, pb->uvs + cc->i1,
			cc->t);
	++pb->uvs_size;
	pb->view_positions[pb->view_positions_size] = wc_p3_lerp(pb->view_positions
			+ cc->i0, pb->view_positions + cc->i1, cc->t);
	cc->out_indices[cc->out_indices_size] = pb->view_positions_size;
	++pb->view_positions_size;
	++cc->out_indices_size;
	cc->out_indices[cc->out_indices_size] = cc->i1;
	++cc->out_indices_size;
	cc->i0 = cc->i1;
}

/*
** 2021-05-05 note:
**
**    p1
**    +
**     \
**      \ (add new, add index)
** ------+------
**  |     \
**  |      \
**  v       +
**  n       p0
*/
static void	zz_clip_going_out(t_pipeline_buffers *pb, t_clip_context *cc)
{
	pb->uvs[pb->uvs_size] = wc_p2_lerp(pb->uvs + cc->i0, pb->uvs + cc->i1,
			cc->t);
	++pb->uvs_size;
	pb->view_positions[pb->view_positions_size] = wc_p3_lerp(pb->view_positions
			+ cc->i0, pb->view_positions + cc->i1, cc->t);
	cc->out_indices[cc->out_indices_size] = pb->view_positions_size;
	++pb->view_positions_size;
	++cc->out_indices_size;
	cc->i0 = cc->i1;
}

/*
** 2021-05-05 note:
**
** -------------
**  |
**  | +-------+
**  v p0      p1
**  n        (add index)
*/
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
