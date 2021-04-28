/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 12:50:55 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/30 07:40:27 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"

#include "wc_client.h"
#include "wc_draw.h"

static void	zz_draw_context_new(t_draw_context *dc, t_client *c)
{
	t_q4	player_orientation;
	t_p3	player_position;
	t_m44	view_from_world;
	t_m44	world_from_object;

	dc->buffers = &c->pipeline_buffers;
	dc->buffers->screen_positions_size = 0;
	dc->buffers->view_positions_size = 0;
	dc->buffers->visible_indices_size = 0;
	dc->frame_buffer = &c->frame_buffer;
	dc->depth_buffer = &c->depth_buffer;
	dc->clip_from_view = wx_m44_new_perspective(c->camera.hfov_rad,
			c->camera.aspect_ratio, c->camera.near, c->camera.far);
	dc->frustum = wx_frustum_new(&dc->clip_from_view);
	player_orientation = (t_q4){0.0f, 0.0f, 0.0f, 1.0f};
	player_position = (t_p3){c->player_position.x, c->player_position.y, 0.0f};
	world_from_object = wx_m44_new_q4_p3(&player_orientation, &player_position);
	view_from_world = wx_m44_new_inverse_q4_p3(&c->camera.orientation,
			&c->camera.position);
	dc->view_from_object = wx_m44_mul_m44(&view_from_world, &world_from_object);
}

void	wc_draw(t_client *c)
{
	t_draw_context	dc;

	zz_draw_context_new(&dc, c);
	wc_draw_clear(&dc);
	wc_draw_mesh(&dc, &c->unit_cube);
	wc_draw_copy(c, dc.frame_buffer);
}
