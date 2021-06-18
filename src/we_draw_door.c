#include "we_draw.h"

/*
** Draw door if ray distance to door is far enough.
*/

void	we_draw_door(t_ray ray, t_frame_buffer *fb,
			t_map_textures *textures)
{
	t_p2	draw_fb;
	t_f32	min_distance;

	if (ray.tile.tiles_id == 2)
	{
		min_distance = WX_TILE_WIDTH * 0.5f;
		if (ray.tile.distance > min_distance
			&& ray.nb * 0.1f < ray.tile.distance)
		{
			draw_fb.x = ray.nb;
			draw_fb.y = ray.view_height * fb->height
				- ray.view_height * ray.tile.projected_height;
			we_draw_texture_wall(&ray, draw_fb, fb, &textures->door);
		}
	}
}
