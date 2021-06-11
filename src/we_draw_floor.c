/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:40:30 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/11 21:14:19 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

/*
** Calculating frame buffer draw end point for floor or ceiling.
*/

static	t_p2	zz_floor_w_to_fb(t_ray *ray, t_u32 fb_height,
	t_f32 draw_end_distance_w, t_bool floor)
{
	t_p2	end;
	t_f32	projected_height;

	projected_height = ray->dist_to_screen_w
		/ draw_end_distance_w * WE_BLOCK_W;
	end.y = ray->view_height * fb_height
		- ray->view_height * projected_height;
	if (floor)
		end.y += projected_height;
	end.x = ray->nb;
	return (end);
}

/*
** Drawing one floor tile.
*/

static void	zz_draw_floor(t_draw_floor draw, t_frame_buffer *fb, t_ray *ray,
				t_tex *tex)
{
	t_u32			color;
	t_f32			pixel_distance;

	draw.start_fb.y += ray->tile.projected_height;
	draw.end_fb = zz_floor_w_to_fb(ray, fb->height,
			draw.end_distance_w, wx_true);
	if (draw.start_fb.y >= fb->height)
		draw.start_fb.y = fb->height - 1;
	if (draw.end_fb.y < 0)
		draw.end_fb.y = 0;
	while (draw.start_fb.y > draw.end_fb.y)
	{
		color = tex->texture[0];
		pixel_distance = (ray->tile.distance * draw.start_fb.y / draw.end_fb.y
				+ draw.end_distance_w * (1 - draw.start_fb.y / draw.end_fb.y));
		we_shade_pixel(&color, pixel_distance);
		we_draw_pixel(draw.start_fb, fb, color);
		draw.start_fb.y--;
	}
}

/*
** Drawing one ceiling tile.
*/

//todo: remove draw ceiling

void	zz_draw_ceiling(t_draw_floor draw, t_frame_buffer *fb, t_ray *ray,
				t_tex *tex)
{
	t_u32			color;
	t_f32			pixel_distance;

	if (draw.start_fb.y < 0)
		draw.start_fb.y = 0;
	if (draw.end_fb.y < fb->height - 1)
		draw.end_fb.y = fb->height - 1;
	draw.end_fb = zz_floor_w_to_fb(ray, fb->height,
			draw.end_distance_w, wx_false);
	while (draw.start_fb.y < draw.end_fb.y)
	{
		color = tex->texture[0];
		pixel_distance = (ray->tile.distance * draw.start_fb.y / draw.end_fb.y
				+ draw.end_distance_w * (1 - draw.start_fb.y / draw.end_fb.y));
		we_shade_pixel(&color, pixel_distance);
		we_draw_pixel(draw.start_fb, fb, color);
		draw.start_fb.y++;
	}
}

/*
** Go through the raycast buffer to draw floor on all the horisontal
** non-wall tiles encountered by the ray in question.
*/

static void	zz_draw_horisontal_tiles(t_ray *ray, t_frame_buffer *fb,
	t_level_texture *texture_type)
{
	t_draw_floor	draw;
	t_u32			i;

	i = 0;
	wx_buffer_set(&draw, sizeof(t_draw_floor), 0);
	while (i < ray->tiles_h_size)
	{
		draw.start_fb.x = ray->nb;
		ray->tile = ray->tiles_h[i];
		draw.start_fb.y = ray->view_height * fb->height
			- ray->view_height * ray->tile.projected_height;
		draw.end_w = we_draw_floor_tile_end(ray);
		draw.delta_w.x = draw.end_w.x - ray->start.x;
		draw.delta_w.y = draw.end_w.y - ray->start.y;
		draw.end_distance_w = sqrtf((draw.delta_w.x * draw.delta_w.x
					+ draw.delta_w.y * draw.delta_w.y));
		draw.end_distance_w *= cosf(wx_to_radians(ray->angle_to_player_d));
		zz_draw_floor(draw, fb, ray, &texture_type->floor);
		i++;
	}
}

/*
** Go through the raycast buffer to draw all the vertical non-wall tiles
** encountered by the ray in question.
*/

void	we_draw_floor(t_ray ray, t_frame_buffer *fb,
			t_level_texture *texture_type)
{
	t_draw_floor	draw;
	t_u32			i;

	i = 0;
	we_draw_floor_player_position(fb, &ray, &texture_type->floor);
	wx_buffer_set(&draw, sizeof(t_draw_floor), 0);
	while (i < ray.tiles_v_size)
	{
		draw.start_fb.x = ray.nb;
		ray.tile = ray.tiles_v[i];
		draw.start_fb.y = ray.view_height * fb->height
			- ray.view_height * ray.tile.projected_height;
		draw.end_w = we_draw_floor_tile_end(&ray);
		draw.delta_w.x = draw.end_w.x - ray.start.x;
		draw.delta_w.y = draw.end_w.y - ray.start.y;
		draw.end_distance_w = sqrtf((draw.delta_w.x * draw.delta_w.x
					+ draw.delta_w.y * draw.delta_w.y));
		draw.end_distance_w *= cosf(wx_to_radians(ray.angle_to_player_d));
		zz_draw_floor(draw, fb, &ray, &texture_type->floor);
		i++;
	}
	zz_draw_horisontal_tiles(&ray, fb, texture_type);
}
