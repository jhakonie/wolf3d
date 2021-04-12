/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_texture_wall.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:29:31 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 23:20:12 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

static t_texture_index	zz_texture_coordinates(t_ray ray, t_p2 draw,
	t_u32 fb_height, t_tex tex)
{
	t_texture_index	tex_index;
	t_u32			block;
	t_f32			in_block_pos;

	if (ray.wall.side == we_horisontal)
	{
		block = (int)(ray.wall.end.x / WE_BLOCK_W);
		in_block_pos = ray.wall.end.x - block * WE_BLOCK_W;
		tex_index.coord.x = in_block_pos / WE_BLOCK_W * tex.width;
	}
	else
	{
		block = (int)(ray.wall.end.y / WE_BLOCK_W);
		in_block_pos = ray.wall.end.y - block * WE_BLOCK_W;
		tex_index.coord.x = in_block_pos / WE_BLOCK_W * tex.height;
	}
	if (ray.wall.compass == we_west || ray.wall.compass == we_south)
		tex_index.coord.x = tex.width - tex_index.coord.x;
	tex_index.coord.y = 0;
	tex_index.increment_y = tex.height / ray.wall.projected_height;
	if (draw.y == 0)
		tex_index.coord.y = tex_index.increment_y * fabsf(0.5f * fb_height
				- 0.5f * ray.wall.projected_height);
	return (tex_index);
}

void	we_draw_texture_wall(t_ray ray, t_p2 draw,
											t_frame_buffer *fb, t_tex tex)
{
	t_texture_index		tex_index;
	t_u32				fb_index;
	t_u32				max_tex_index;
	t_u32				color;

	fb_index = 0;
	max_tex_index = tex.height * tex.width;
	tex_index = zz_texture_coordinates(ray, draw, fb->height, tex);
	while (fb_index < ray.wall.projected_height)
	{
		tex_index.index = ((int)tex_index.coord.y * tex.width
				+ (int)tex_index.coord.x);
		if (tex_index.index < max_tex_index)
		{
			if (ray.wall.chart_id == 1)
				color = tex.texture[tex_index.index];
			else
				color = tex.fractal[tex_index.index];
			we_shade_pixel(ray, &color, 3);
			we_draw_pixel(draw, fb, color);
		}
		draw.y++;
		tex_index.coord.y += tex_index.increment_y;
		fb_index++;
	}
}
