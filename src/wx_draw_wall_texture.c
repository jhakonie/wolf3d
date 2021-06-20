/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_texture_wall.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:29:31 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/19 20:25:35 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_draw.h"

static t_texture_index	zz_texture_coordinates(t_ray *ray, t_p2 draw,
	t_texture *texture)
{
	t_texture_index	tex_index;
	t_u32			block;
	t_f32			in_block_pos;

	if (ray->tile.side == we_horisontal)
	{
		block = (int)(ray->tile.hit.x / WX_TILE_WIDTH);
		in_block_pos = ray->tile.hit.x - block * WX_TILE_WIDTH;
		tex_index.coord.x = in_block_pos / WX_TILE_WIDTH * texture->width;
	}
	else
	{
		block = (int)(ray->tile.hit.y / WX_TILE_WIDTH);
		in_block_pos = ray->tile.hit.y - block * WX_TILE_WIDTH;
		tex_index.coord.x = in_block_pos / WX_TILE_WIDTH * texture->height;
	}
	if (ray->tile.compass == we_west || ray->tile.compass == we_south)
		tex_index.coord.x = texture->width - tex_index.coord.x;
	tex_index.coord.y = 0;
	tex_index.increment_y = texture->height / ray->tile.projected_height;
	if (draw.y < 0)
		tex_index.coord.y = tex_index.increment_y
			* fabsf(draw.y);
	return (tex_index);
}

static void	zz_clip(t_p2 *draw, t_u32 fb_height, t_u32 *max_y_fb)
{
	if (*max_y_fb > fb_height - 1)
		*max_y_fb = fb_height - 1;
	if (draw->y < 0)
		draw->y = 0;
}

void	wx_draw_wall_texture(t_ray *ray, t_p2 draw,
			t_frame_buffer *fb, t_texture *texture)
{
	t_texture_index		tex_index;
	t_u32				max_tex_index;
	t_u32				color;
	t_u32				max_y_fb;

	max_tex_index = texture->height * texture->width;
	tex_index = zz_texture_coordinates(ray, draw, texture);
	max_y_fb = draw.y + ray->tile.projected_height;
	zz_clip(&draw, fb->height, &max_y_fb);
	while (draw.y < max_y_fb)
	{
		tex_index.index = ((t_u32)tex_index.coord.y * texture->width
				+ (t_u32)tex_index.coord.x);
		if (tex_index.index < max_tex_index)
		{
			wx_buffer_copy(&color, texture->buffer + (tex_index.index * 4),
				sizeof(color));
			wx_shade_pixel(&color, ray->tile.distance);
			wx_draw_pixel(draw, fb, color);
		}
		draw.y++;
		tex_index.coord.y += tex_index.increment_y;
	}
}
