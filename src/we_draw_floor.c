/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:40:30 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/17 14:33:18 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"
#include "stdio.h"

/*
** Calculating frame buffer draw end point for floor or ceiling.
*/

static	t_p2	zz_floor_w_to_fb(t_p2 draw_end_w, t_ray ray,
	t_u32 fb_height, t_bool floor)
{
	t_p2	end;
	t_f32	distance;
	t_f32	projected_height;

	distance = sqrtf(powf((draw_end_w.x - ray.start.x), 2.0f)
			+ powf((draw_end_w.y - ray.start.y), 2.0f));
	distance *= cosf(wx_to_radians(ray.angle_to_player_d));
	projected_height = ray.dist_to_screen / distance * WE_BLOCK_W;
	end.y = ray.player_height * fb_height
		- ray.player_height * projected_height;
	if (floor == wx_true)
		end.y += projected_height;
	end.x = ray.nb;
	return (end);
}

static void	zz_draw_floor(t_ray ray, t_frame_buffer *fb, t_p2 draw_end_w,
	t_f32 draw_end_distance_w)
{
	t_p2			draw_start_fb;
	t_p2			draw_end_fb;
	t_u32			color;
	t_f32			pixel_distance;
	static t_tex	tex = (t_tex){3, 2,
		{0x0aff00, 0x0dbb00, 0x00ba00,
			0x0ebc00, 0x00bda0, 0x00be00},
		6,
		WX_NULL
	};

	draw_start_fb.x = ray.nb;
	draw_start_fb.y = ray.player_height * fb->height
		- ray.player_height * ray.wall.projected_height
		+ ray.wall.projected_height;
	draw_end_fb = zz_floor_w_to_fb(draw_end_w, ray, fb->height, wx_true);
	while (draw_start_fb.y > draw_end_fb.y)
	{
		color = tex.fractal[ray.wall.chart_index % 6];
		pixel_distance = (ray.wall.distance * draw_start_fb.y / draw_end_fb.y
				+ draw_end_distance_w * (1 - draw_start_fb.y / draw_end_fb.y));
		we_shade_pixel(&color, ray, pixel_distance, 5);
		we_draw_pixel(draw_start_fb, fb, color);
		draw_start_fb.y--;
	}
}

static void	zz_draw_ceiling(t_ray ray, t_frame_buffer *fb, t_p2 draw_end_w,
	t_f32 draw_end_distance_w)
{
	t_p2			draw_start_fb;
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

	draw_start_fb.x = ray.nb;
	draw_start_fb.y = ray.player_height * fb->height
		- ray.player_height * ray.wall.projected_height;
	draw_end_fb = zz_floor_w_to_fb(draw_end_w, ray, fb->height, wx_false);
	while (draw_start_fb.y < draw_end_fb.y)
	{
		color = tex.fractal[ray.wall.chart_index % 9];
		pixel_distance = (ray.wall.distance * draw_start_fb.y / draw_end_fb.y
				+ draw_end_distance_w * (1 - draw_start_fb.y / draw_end_fb.y));
		we_shade_pixel(&color, ray, pixel_distance, 5);
		we_draw_pixel(draw_start_fb, fb, color);
		draw_start_fb.y++;
	}
}

void	we_draw_floor(t_ray ray, t_frame_buffer *fb, t_bool draw_3d)
{
	t_p2	draw_end_w;
	t_f32	draw_end_distance_w;

	draw_end_w = we_floor_draw_end(ray);
	draw_end_distance_w = (sqrtf(pow((draw_end_w.x - ray.start.x), 2)
				+ pow((draw_end_w.y - ray.start.y), 2)));
	if (draw_3d == wx_true)
	{
		zz_draw_floor(ray, fb, draw_end_w, draw_end_distance_w);
		zz_draw_ceiling(ray, fb, draw_end_w, draw_end_distance_w);
	}
}
