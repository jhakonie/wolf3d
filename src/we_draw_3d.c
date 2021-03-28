/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:10:51 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/29 00:14:41 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static t_texture	zz_wall_texture(t_ray ray)
{
	if (ray.wall.compass == we_north)
		return ((t_texture){3, 3,
			{0x0000ff, 0x0000ff, 0x0000ff,
				0xffffff, 0xffffff, 0xffffff,
				0xffffff, 0xffffff, 0xffffff},
		});
	else if (ray.wall.compass == we_west)
		return ((t_texture){3, 3,
			{0xffffff, 0xffffff, 0xffffff,
				0x0000ff, 0x0000ff, 0x0000ff,
				0xffffff, 0xffffff, 0xffffff},
		});
	else if (ray.wall.compass == we_south)
		return ((t_texture){3, 3,
			{0xffffff, 0xffffff, 0xffffff,
				0xffffff, 0xffffff, 0xffffff,
				0x0000ff, 0x0000ff, 0x0000ff},
		});
	return ((t_texture){3, 3,
		{0x0000ff, 0x0000ff, 0x0000ff,
			0xffffff, 0xffffff, 0xffffff,
			0x0000ff, 0x0000ff, 0x0000ff},
	});
}

static void	zz_draw_wall_to_buffer(t_ray ray, t_frame_buffer *fb)
{
	t_u32		i;
	t_p2		draw_start;
	t_texture	tex;

	i = 0;
	tex = zz_wall_texture(ray);
	if (ray.wall.distance > 0)
		ray.wall.projected_height = (ray.dist_to_screen / ray.wall.distance)
			* WE_BLOCK_W;
	draw_start.y = 0.5 * fb->height - 0.5 * ray.wall.projected_height;
	if ((int)draw_start.y < 0)
		draw_start.y = 0;
	draw_start.x = (t_f32)ray.nb;
	we_draw_texture(ray, draw_start, fb, tex);
}

void	we_draw_3d(t_frame_buffer *frame_buffer, t_player player,
	t_map map)
{
	t_f32	angle_d;
	t_ray	ray;

	angle_d = 0;
	if (map.draw_3d == wx_true)
		wx_buffer_set(frame_buffer->data, frame_buffer->data_size, 0);
	we_ray_init(&ray, player.fov_d, frame_buffer->width, player.position);
	while (ray.nb < frame_buffer->width)
	{
		we_ray_calculate(&ray, angle_d, player.direction_d);
		we_ray_cast(&ray, map.chart);
		if (map.draw_3d == wx_true)
			zz_draw_wall_to_buffer(ray, frame_buffer);
		else if ((map.draw_rays))
			we_draw_rays(ray, map, frame_buffer);
		angle_d += ray.angle_increment_d;
		ray.nb++;
	}
}
