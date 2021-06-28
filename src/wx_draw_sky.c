#include "we_draw.h"

static t_texture_index	zz_texture_coordinates(t_ray *ray, t_p2 draw,
	t_texture *texture)
{
	t_texture_index	tex_index;

	if (ray->tile.side == we_horisontal)
		tex_index.coord.x = (fabsf(-ray->world_end_w * 2 - ray->tile.hit.x)
				/ (5 * ray->world_end_w - WX_TILE_WIDTH)) * texture->width;
	else
		tex_index.coord.x = (fabsf(-ray->world_end_w * 2 - ray->tile.hit.y)
				/ (5 * ray->world_end_w - WX_TILE_WIDTH)) * texture->height;
	tex_index.coord.y = 0;
	tex_index.increment_y = texture->height / ray->tile.projected_height;
	if (draw.y < 0)
		tex_index.coord.y = tex_index.increment_y
			* fabsf(draw.y);
	return (tex_index);
}

static void	zz_draw_sky_under_floor(t_ray *ray, t_p2 draw,
			t_frame_buffer *fb, t_texture *texture)
{
	t_texture_index		tex_index;
	t_u32				max_tex_index;
	t_u32				color;

	max_tex_index = texture->height * texture->width;
	tex_index = zz_texture_coordinates(ray, draw, texture);
	while (draw.y < fb->height - 1)
	{
		tex_index.index = ((t_u32)tex_index.coord.y * texture->width
				+ (t_u32)tex_index.coord.x);
		if (tex_index.index < max_tex_index)
		{
			wx_buffer_copy(&color, texture->buffer + (tex_index.index * 4),
				sizeof(color));
			wx_draw_pixel(draw, fb, color);
		}
		draw.y++;
		tex_index.coord.y += tex_index.increment_y;
	}
}

static void	zz_draw_sky(t_ray *ray, t_p2 draw,
			t_frame_buffer *fb, t_texture *texture)
{
	t_texture_index		tex_index;
	t_u32				max_tex_index;
	t_u32				color;

	max_tex_index = texture->height * texture->width;
	tex_index = zz_texture_coordinates(ray, draw, texture);
	while (draw.y > 0)
	{
		tex_index.index = ((t_u32)tex_index.coord.y * texture->width
				+ (t_u32)tex_index.coord.x);
		if (tex_index.index < max_tex_index)
		{
			wx_buffer_copy(&color, texture->buffer + (tex_index.index * 4),
				sizeof(color));
			wx_draw_pixel(draw, fb, color);
		}
		draw.y--;
		tex_index.coord.y += tex_index.increment_y;
	}
}

void	wx_draw_sky(t_frame_buffer *fb, t_ray ray, t_texture *skys)
{
	t_p2			draw_start;
	t_p2			delta;

	ray.tile = wx_ray_cast_sky(&ray);
	delta.x = ray.tile.hit.x - ray.start.x;
	delta.y = ray.tile.hit.y - ray.start.y;
	ray.tile.distance = sqrtf(delta.x * delta.x + delta.y * delta.y);
	ray.tile.distance *= cosf(wx_to_radians(ray.angle_to_player_d));
	ray.tile.projected_height = (ray.dist_to_screen_w / ray.tile.distance)
		* ray.world_end_w * 3;
	draw_start.y = ray.view_height * fb->height;
	if ((t_s32)draw_start.y >= (t_s32)fb->height)
		draw_start.y = fb->height - 1;
	draw_start.x = (t_f32)ray.nb;
	zz_draw_sky(&ray, draw_start, fb, &skys[ray.tile.compass]);
	zz_draw_sky_under_floor(&ray, draw_start, fb, &skys[ray.tile.compass]);
}
