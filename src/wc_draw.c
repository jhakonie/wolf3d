/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 12:50:55 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/06 14:48:34 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"

#include "wc_client.h"
#include "wc_draw.h"

static void	zz_draw_others(t_client *c, t_draw_context *dc)
{
	t_p4			hp;
	t_u64			i;
	t_p3			p;

	dc->object_orientation = (t_q4){0.0f, 0.0f, 0.0f, 1.0f};
	p = (t_p3){0.0f, 0.0f, 0.0f};
	i = 0;
	while (i < c->other_positions_size)
	{
		dc->object_position = (t_p3){c->other_positions[i].x,
			c->other_positions[i].y, 0.0f};
		dc->world_from_object = wx_m44_new_q4_p3(&dc->object_orientation,
			&dc->object_position);
		p = wx_m44_mul_p3(&dc->world_from_object, &p);
		p = wx_m44_mul_p3(&dc->view_from_world, &p);
		hp = (t_p4){p.x, p.y, p.z, 1.0f};
		hp = wx_m44_mul_p4(&dc->clip_from_view, &hp);
		p = (t_p3){hp.x / hp.w, hp.y / hp.w, hp.z / hp.w};
		p = (t_p3){(-p.x + 1.0f) * (0.5f * c->frame_buffer.width),
			(-p.y + 1.0f) * (0.5f * c->frame_buffer.height), p.z};
		wc_draw_rectangle_outline(&c->frame_buffer, p, 20, 0xff666666);
		++i;
	}
}

static void	zz_draw_player(t_client *c, t_draw_context *dc)
{
	t_p4			hp;
	t_p3			p;

	dc->object_orientation = (t_q4){0.0f, 0.0f, 0.0f, 1.0f};
	dc->object_position = (t_p3){c->player_position.x, c->player_position.y,
		0.0f};
	dc->world_from_object = wx_m44_new_q4_p3(&dc->object_orientation,
		&dc->object_position);
	dc->view_from_world = wx_m44_new_inverse_q4_p3(&c->camera.orientation,
		&c->camera.position);
	dc->clip_from_view = wx_m44_new_perspective(c->camera.hfov_rad,
		c->camera.aspect_ratio, c->camera.near, c->camera.far);
	p = (t_p3){0.0f, 0.0f, 0.0f};
	p = wx_m44_mul_p3(&dc->world_from_object, &p);
	p = wx_m44_mul_p3(&dc->view_from_world, &p);
	hp = (t_p4){p.x, p.y, p.z, 1.0f};
	hp = wx_m44_mul_p4(&dc->clip_from_view, &hp);
	p = (t_p3){hp.x / hp.w, hp.y / hp.w, hp.z / hp.w};
	p = (t_p3){(-p.x + 1.0f) * (0.5f * c->frame_buffer.width),
		(-p.y + 1.0f) * (0.5f * c->frame_buffer.height), p.z};
	wc_draw_rectangle_solid(&c->frame_buffer, p, 20, 0xff00aaff);
}

void		wc_draw(t_client *c)
{
	t_draw_context	dc;

	dc.view_from_world = wx_m44_new_inverse_q4_p3(&c->camera.orientation,
		&c->camera.position);
	dc.clip_from_view = wx_m44_new_perspective(c->camera.hfov_rad,
		c->camera.aspect_ratio, c->camera.near, c->camera.far);
	wc_draw_clear(&c->frame_buffer);
	zz_draw_player(c, &dc);
	zz_draw_others(c, &dc);
	wc_draw_copy(c, &c->frame_buffer);
}
