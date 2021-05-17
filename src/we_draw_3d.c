/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:10:51 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/17 16:15:45 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static void	zz_fractal_init(t_p2 player_pos, t_wall_type *wall_type)
{
	wall_type[1].wall[we_north]
		= we_fractal_texture_create(player_pos, &we_julia, we_north);
	wall_type[1].wall[we_east]
		= we_fractal_texture_create(player_pos, &we_mandelbrot, we_east);
	wall_type[1].wall[we_west]
		= we_fractal_texture_create(player_pos, &we_snowflake, we_west);
	wall_type[1].wall[we_south] = (t_tex){3, 3,
	{0x00ff00, 0xff00ff, 0xff0000,
		0x00ff00, 0xff00ff, 0xff0000,
		0x00ff00, 0xff00ff, 0xff0000},
		0,
		WX_NULL
	};
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
	zz_fractal_init(player.position, map.wall_type);
	ray.player_height = player.height;
	ray.dist_to_screen = player.dist_to_screen;
	while (ray.nb < frame_buffer->width)
	{
		we_ray_calculate(&ray, angle_d, player.direction_d);
		we_ray_cast(&ray, map.tiles, frame_buffer, map.draw_3d);
		if (map.draw_3d == wx_true)
			we_draw_wall(ray, frame_buffer, map.wall_type);
		else if ((map.draw_rays))
			we_draw_rays(ray, map, frame_buffer);
		angle_d += ray.angle_increment_d;
		ray.nb++;
	}
}
