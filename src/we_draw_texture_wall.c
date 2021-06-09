/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_texture_wall.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:29:31 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/09 12:39:57 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

static t_texture_index	zz_texture_coordinates(t_ray *ray, t_p2 draw,
	t_tex *tex)
{
	t_texture_index	tex_index;
	t_u32			block;
	t_f32			in_block_pos;

	if (ray->tile.side == we_horisontal)
	{
		block = (int)(ray->tile.hit.x / WE_BLOCK_W);
		in_block_pos = ray->tile.hit.x - block * WE_BLOCK_W;
		tex_index.coord.x = in_block_pos / WE_BLOCK_W * tex->width;
	}
	else
	{
		block = (int)(ray->tile.hit.y / WE_BLOCK_W);
		in_block_pos = ray->tile.hit.y - block * WE_BLOCK_W;
		tex_index.coord.x = in_block_pos / WE_BLOCK_W * tex->height;
	}
	if (ray->tile.compass == we_west || ray->tile.compass == we_south)
		tex_index.coord.x = tex->width - tex_index.coord.x;
	tex_index.coord.y = 0;
	tex_index.increment_y = tex->height / ray->tile.projected_height;
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

void	we_draw_texture_wall(t_ray *ray, t_p2 draw,
											t_frame_buffer *fb, t_tex *tex)
{
	t_texture_index		tex_index;
	t_u32				max_tex_index;
	t_u32				color;
	t_u32				max_y_fb;

	max_tex_index = tex->height * tex->width;
	tex_index = zz_texture_coordinates(ray, draw, tex);
	max_y_fb = draw.y + ray->tile.projected_height;
	zz_clip(&draw, fb->height, &max_y_fb);
	while (draw.y < max_y_fb)
	{
		tex_index.index = ((t_u32)tex_index.coord.y * tex->width
				+ (t_u32)tex_index.coord.x);
		if (tex_index.index < max_tex_index)
		{
			color = tex->texture[tex_index.index];
			we_shade_pixel(&color, ray->tile.distance);
			we_draw_pixel(draw, fb, color);
		}
		draw.y++;
		tex_index.coord.y += tex_index.increment_y;
	}
}
