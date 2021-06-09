#include "we_draw.h"

static t_texture_index	zz_texture_coordinates(t_ray *ray, t_p2 draw,
	t_tex *tex)
{
	t_texture_index	tex_index;

	if (ray->tile.side == we_horisontal)
		tex_index.coord.x = (fabsf(-ray->world_end_w - ray->tile.hit.x)
				/ (3 * ray->world_end_w)) * tex->width;
	else
		tex_index.coord.x = (fabsf(-ray->world_end_w - ray->tile.hit.y)
				/ (3 * ray->world_end_w)) * tex->height;
	tex_index.coord.y = 0;
	tex_index.increment_y = tex->height / ray->tile.projected_height;
	if (draw.y < 0)
		tex_index.coord.y = tex_index.increment_y
			* fabsf(draw.y);
	return (tex_index);
}

static void	zz_draw_sky_under_floor(t_ray *ray, t_p2 draw,
			t_frame_buffer *fb, t_tex *tex)
{
	t_texture_index		tex_index;
	t_u32				max_tex_index;
	t_u32				color;

	max_tex_index = tex->height * tex->width;
	tex_index = zz_texture_coordinates(ray, draw, tex);
	while (draw.y < fb->height - 1)
	{
		tex_index.index = ((t_u32)tex_index.coord.y * tex->width
				+ (t_u32)tex_index.coord.x);
		if (tex_index.index < max_tex_index)
		{
			color = tex->texture[tex_index.index];
			we_draw_pixel(draw, fb, color);
		}
		draw.y++;
		tex_index.coord.y += tex_index.increment_y;
	}
}

static void	zz_draw_sky(t_ray *ray, t_p2 draw,
			t_frame_buffer *fb, t_tex *tex)
{
	t_texture_index		tex_index;
	t_u32				max_tex_index;
	t_u32				color;

	max_tex_index = tex->height * tex->width;
	tex_index = zz_texture_coordinates(ray, draw, tex);
	while (draw.y > 0)
	{
		tex_index.index = ((t_u32)tex_index.coord.y * tex->width
				+ (t_u32)tex_index.coord.x);
		if (tex_index.index < max_tex_index)
		{
			color = tex->texture[tex_index.index];
			we_draw_pixel(draw, fb, color);
		}
		draw.y--;
		tex_index.coord.y += tex_index.increment_y;
	}
}

void	we_draw_sky(t_frame_buffer *fb, t_ray ray, t_tex *sky)
{
	t_p2			draw_start;

	ray.tile = we_ray_cast_sky(&ray);
	if (ray.tile.side != we_no_wall)
	{
		ray.tile.projected_height = ray.world_end_w * 2;
		draw_start.y = ray.view_height * fb->height;
		if ((t_s32)draw_start.y >= (t_s32)fb->height)
			draw_start.y = fb->height - 1;
		draw_start.x = (t_f32)ray.nb;
		zz_draw_sky(&ray, draw_start, fb, sky);
		zz_draw_sky_under_floor(&ray, draw_start, fb, sky);
	}
}
