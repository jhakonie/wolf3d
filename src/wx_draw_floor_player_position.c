#include "we_draw.h"

static	t_p2	zz_floor_w_to_fb(t_ray *ray, t_u32 fb_height,
	t_f32 draw_end_distance_w)
{
	t_p2	end;
	t_f32	projected_height;

	projected_height = ray->dist_to_screen_w
		/ draw_end_distance_w * WX_TILE_WIDTH;
	end.y = ray->view_height * fb_height
		- ray->view_height * projected_height;
	end.y += projected_height;
	end.x = ray->nb;
	return (end);
}

static void	zz_clip(t_p2 *draw_end_fb)
{
	if (draw_end_fb->x < 0)
		draw_end_fb->x = 0;
	if (draw_end_fb->y < 0)
		draw_end_fb->y = 0;
}

void	wx_draw_floor_player_position(t_frame_buffer *fb, t_ray *ray,
			t_texture *t)
{
	t_u32			color;
	t_draw_floor	draw;

	draw.start_fb.x = ray->nb;
	draw.start_fb.y = fb->height - 1;
	ray->tile.hit = ray->start;
	draw.end_w = wx_draw_floor_tile_end(ray);
	draw.delta_w.x = fabsf(draw.end_w.x - ray->start.x);
	draw.delta_w.y = fabsf(draw.end_w.y - ray->start.y);
	draw.end_distance_w = sqrtf((draw.delta_w.x * draw.delta_w.x
				+ draw.delta_w.y * draw.delta_w.y));
	draw.end_distance_w *= cosf(wx_to_radians(ray->angle_to_player_d));
	draw.end_fb = zz_floor_w_to_fb(ray, fb->height,
			draw.end_distance_w);
	zz_clip(&draw.end_fb);
	while (draw.start_fb.y > draw.end_fb.y)
	{
		wx_buffer_copy(&color, t->buffer, sizeof(color));
		wx_draw_pixel(draw.start_fb, fb, color);
		draw.start_fb.y--;
	}
}
