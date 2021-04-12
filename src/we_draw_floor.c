/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:40:30 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 23:25:06 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

/*
** Calculating frame buffer draw end point for floor or ceiling.
*/

static	t_p2	zz_draw_end_fb(t_p2 draw_end_w, t_ray ray,
	t_u32 fb_height, t_bool floor)
{
	t_p2	end;
	t_f32	distance;
	t_f32	projected_height;

	distance = sqrtf(powf((draw_end_w.x - ray.start.x), 2.0f)
			+ powf((draw_end_w.y - ray.start.y), 2.0f));
	distance *= cosf(wx_to_radians(ray.angle_to_player_d));
	projected_height = (ray.dist_to_screen / distance) * WE_BLOCK_W;
	end.y = 0.5f * fb_height - 0.5f * projected_height;
	if (floor == wx_true)
		end.y += projected_height;
	end.x = ray.nb;
	return (end);
}

static void	zz_draw_ceiling(t_ray ray, t_frame_buffer *fb, t_p2 draw_end_w)
{
	t_p2	draw_start_fb;
	t_p2	draw_end_fb;
	t_u32	color;

	color = 0x000fff;
	draw_start_fb.x = ray.nb;
	draw_start_fb.y = 0.5f * fb->height - 0.5f * ray.wall.projected_height;
	draw_end_fb = zz_draw_end_fb(draw_end_w, ray, fb->height, wx_false);
	if (ray.wall.chart_index % 3 == 0)
		color = 0xff00ff;
	we_shade_pixel(ray, &color, 7);
	we_draw_line(draw_start_fb, draw_end_fb, fb, color);
}

void	we_draw_floor(t_ray ray, t_frame_buffer *fb, t_bool draw_3d)
{
	t_p2	draw_start_fb;
	t_p2	draw_end_fb;
	t_p2	draw_end_w;
	t_u32	color;
	t_f32	floor_height;

	color = 0x0000ff;
	if (ray.wall.chart_id != 1 && draw_3d == wx_true)
	{
		draw_start_fb.x = ray.nb;
		draw_start_fb.y = 0.5f * fb->height - 0.5f * ray.wall.projected_height
			+ ray.wall.projected_height;
		draw_end_w = we_floor_draw_end(ray);
		draw_end_fb = zz_draw_end_fb(draw_end_w, ray, fb->height, wx_true);
		floor_height = fabsf(draw_start_fb.y - draw_end_fb.y);
		if (ray.wall.chart_index % 4 == 0)
			color = 0x00ff00;
		we_shade_pixel(ray, &color, 7);
		we_draw_line(draw_start_fb, draw_end_fb, fb, color);
		zz_draw_ceiling(ray, fb, draw_end_w);
	}
}
