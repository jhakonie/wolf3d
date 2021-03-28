/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:29:31 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/28 23:22:59 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static t_texture_index	zz_texture_coordinates(t_ray ray, t_p2 draw,
												t_u32 fb_height, t_texture tex)
{
	t_texture_index	tex_index;
	t_u32			block;
	t_f32			in_block_pos;

	if (ray.wall.side == we_horisontal)
	{
		block = (int)(ray.wall.end.x / WE_BLOCK_W);
		in_block_pos = ray.wall.end.x - block * WE_BLOCK_W;
	}
	else
	{
		block = (int)(ray.wall.end.y / WE_BLOCK_W);
		in_block_pos = ray.wall.end.y - block * WE_BLOCK_W;
	}
	tex_index.coord.x = in_block_pos / WE_BLOCK_W * tex.width;
	tex_index.coord.y = 0;
	tex_index.increment_y = tex.height / ray.wall.projected_height;
	if (draw.y == 0)
		tex_index.coord.y = tex_index.increment_y * fabs(0.5 * fb_height - 0.5
				* ray.wall.projected_height);
	tex_index.index = ((int)tex_index.coord.y * tex.width
			+ (int)tex_index.coord.x);
	return (tex_index);
}

void	we_draw_texture(t_ray ray, t_p2 draw,
											t_frame_buffer *fb, t_texture tex)
{
	t_texture_index		tex_index;
	t_u32				fb_index;
	t_u32				max_tex_index;
	t_u32				color;

	fb_index = 0;
	color = 0;
	max_tex_index = tex.height * tex.width;
	tex_index = zz_texture_coordinates(ray, draw, fb->height, tex);
	while (fb_index < ray.wall.projected_height)
	{
		tex_index.index = ((int)tex_index.coord.y * tex.width
				+ (int)tex_index.coord.x);
		if (tex_index.index < max_tex_index)
		{
			color = tex.texture[tex_index.index];
			we_draw_pixel(draw, fb, color);
		}
		draw.y++;
		tex_index.coord.y += tex_index.increment_y;
		fb_index++;
	}
}
