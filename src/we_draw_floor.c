/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:40:30 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/17 17:06:27 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

/*
** Calculating frame buffer draw end point for floor or ceiling.
*/
static	t_p2	zz_floor_w_to_fb(t_ray ray, t_u32 fb_height,
	t_f32 draw_end_distance_w, t_bool floor)
{
	t_p2	end;
	t_f32	projected_height;

	projected_height = ray.dist_to_screen / draw_end_distance_w * WE_BLOCK_W;
	end.y = ray.player_height * fb_height
		- ray.player_height * projected_height;
	if (floor)
		end.y += projected_height;
	end.x = ray.nb;
	return (end);
}

static void	zz_draw_floor(t_frame_buffer *fb, t_p2 draw_start_fb, t_ray ray,
	t_f32 draw_end_distance_w)
{
	t_p2			draw_end_fb;
	t_u32			color;
	t_f32			pixel_distance;
	static t_tex	tex = (t_tex){3, 2,
		{0x0aff00, 0x0dbb00, 0x00ba00,
			0x0ebc00, 0x00bda0, 0x00be00},
		6,
		WX_NULL
	};

	draw_start_fb.y += ray.wall.projected_height;
	draw_end_fb = zz_floor_w_to_fb(ray, fb->height,
			draw_end_distance_w, wx_true);
	while (draw_start_fb.y > draw_end_fb.y)
	{
		color = tex.fractal[ray.wall.tiles_index % 6];
		pixel_distance = (ray.wall.distance * draw_start_fb.y / draw_end_fb.y
				+ draw_end_distance_w * (1 - draw_start_fb.y / draw_end_fb.y));
		we_shade_pixel(&color, ray, pixel_distance, 5);
		we_draw_pixel(draw_start_fb, fb, color);
		draw_start_fb.y--;
	}
}

static void	zz_draw_ceiling(t_frame_buffer *fb, t_p2 draw_start_fb, t_ray ray,
	t_f32 draw_end_distance_w)
{
	t_p2			draw_end_fb;
	t_u32			color;
	t_f32			pixel_distance;
	static t_tex	tex = (t_tex){3, 3,
	{0x0aff00, 0x0dbbc0, 0x00ba00,
			0x0ebc00, 0x00bda0, 0x00bed0,
			0x0dbf00, 0x0cbbc0, 0x00ba00},
		9,
		WX_NULL
	};

	draw_end_fb = zz_floor_w_to_fb(ray, fb->height,
			draw_end_distance_w, wx_false);
	while (draw_start_fb.y < draw_end_fb.y)
	{
		color = tex.fractal[ray.wall.tiles_index % 9];
		pixel_distance = (ray.wall.distance * draw_start_fb.y / draw_end_fb.y
				+ draw_end_distance_w * (1 - draw_start_fb.y / draw_end_fb.y));
		we_shade_pixel(&color, ray, pixel_distance, 5);
		we_draw_pixel(draw_start_fb, fb, color);
		draw_start_fb.y++;
	}
}

void	we_draw_floor(t_ray ray, t_frame_buffer *fb, t_bool draw_3d)
{
	t_p2	draw_start_fb;
	t_p2	delta_w;
	t_f32	draw_end_distance_w;
	t_p2	draw_end_w;

	draw_start_fb.x = ray.nb;
	draw_start_fb.y = ray.player_height * fb->height
		- ray.player_height * ray.wall.projected_height;
	draw_end_w = we_floor_draw_end(ray);
	delta_w.x = draw_end_w.x - ray.start.x;
	delta_w.y = draw_end_w.y - ray.start.y;
	draw_end_distance_w = sqrtf((delta_w.x * delta_w.x + delta_w.y
				* delta_w.y));
	draw_end_distance_w *= cosf(wx_to_radians(ray.angle_to_player_d));
	if (draw_3d == wx_true)
	{
		zz_draw_floor(fb, draw_start_fb, ray, draw_end_distance_w);
		zz_draw_ceiling(fb, draw_start_fb, ray, draw_end_distance_w);
	}
}
