#include "we_draw.h"

/*
** Draw door if ray distance to door is far enough.
*/

void	we_draw_door(t_ray ray, t_frame_buffer *fb,
			t_level_texture *texture_type)
{
	t_p2	draw_fb;
	t_f32	min_distance;
	t_f32	ray_to_draw;

	if (ray.tile.tiles_id == 2)
	{
		min_distance = WE_BLOCK_W * 0.5f;
		ray_to_draw = ray.nb * 0.1f;
		if (ray.tile.distance > min_distance
			&& ray.nb * 0.1f < ray.tile.distance)
		{
			draw_fb.x = ray.nb;
			draw_fb.y = ray.view_height * fb->height
				- ray.view_height * ray.tile.projected_height;
			we_draw_texture_wall(&ray, draw_fb, fb, &texture_type->door);
		}
	}
}
