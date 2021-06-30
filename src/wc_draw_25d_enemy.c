#include "wc_draw.h"
#include "wc_client.h"
#include "wx_draw.h"

/*
** Calculating frame buffer draw end point for floor or ceiling.
*/

static	t_p2	zz_floor_w_to_fb(t_ray *ray, t_u32 fb_height,
	t_f32 draw_end_distance_w, t_bool floor)
{
	t_p2	end;
	t_f32	projected_height;

	projected_height = ray->dist_to_screen_w
		/ draw_end_distance_w * WX_TILE_WIDTH;
	end.y = ray->view_height * fb_height
		- ray->view_height * projected_height;
	if (floor)
		end.y += 0.5f * projected_height;
	end.x = ray->nb;
	return (end);
}

static void	zz_draw_floor(t_draw_floor draw, t_frame_buffer *fb, t_ray *ray,
				t_texture *texture)
{
	t_u32			color;
	t_u32			texture_index;
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
		texture_index = (float)ray->tile.tiles_index / WX_MAP_SIZE
			* texture->height * texture->width;
		wx_buffer_copy(&color, texture->buffer + (texture_index * 4),
			sizeof(color));
		pixel_distance = (ray->tile.distance * draw.start_fb.y / draw.end_fb.y
				+ draw.end_distance_w * (1 - draw.start_fb.y / draw.end_fb.y));
		wx_shade_pixel(&color, pixel_distance);
		wx_draw_pixel(draw.start_fb, fb, color);
		draw.start_fb.y--;
	}
}

void	wc_draw_25d_enemy(t_frame_buffer *fb, t_ray *ray,
			t_texture *texture)
{
	t_p2			draw_wall_start;
	t_draw_floor	draw;

	draw_wall_start.y = ray->view_height * fb->height
		- ray->view_height * ray->tile.projected_height
		+ 0.5f * ray->tile.projected_height;
	if ((t_s32)draw_wall_start.y >= (t_s32)fb->height)
		return ;
	ray->tile.projected_height *= 0.5f;
	draw_wall_start.x = (t_f32)ray->nb;
	wx_draw_wall_texture(ray, draw_wall_start, fb, texture);
	ray->tile.projected_height *= 2;
	draw.start_fb.x = ray->nb;
	draw.start_fb.y = ray->view_height * fb->height
		- ray->view_height * ray->tile.projected_height
		- 0.5f * ray->tile.projected_height;
	draw.end_w = wx_draw_floor_tile_end(ray);
	draw.delta_w.x = draw.end_w.x - ray->start.x;
	draw.delta_w.y = draw.end_w.y - ray->start.y;
	draw.end_distance_w = sqrtf((draw.delta_w.x * draw.delta_w.x
				+ draw.delta_w.y * draw.delta_w.y));
	draw.end_distance_w *= cosf(wx_to_radians(ray->angle_to_player_d));
	zz_draw_floor(draw, fb, ray, texture);
}
