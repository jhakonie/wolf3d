/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:10:51 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/19 15:22:08 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_draw.h"

void	we_draw_3d(t_frame_buffer *frame_buffer, t_player player,
	t_map *m)
{
	t_f32	angle_d;
	t_ray	ray;

	angle_d = 0;
	wx_buffer_set(frame_buffer->data, frame_buffer->data_size, 0);
	wx_buffer_set(&ray, sizeof(t_ray), 0);
	we_ray_init(&ray, player.fov_d, frame_buffer->width, player.position);
	ray.view_height = player.height;
	while (ray.nb < frame_buffer->width)
	{
		ray.tile_type_to_find = WE_WALL;
		we_draw_sky(frame_buffer, ray, &m->textures.sky);
		we_ray_calculate(&ray, angle_d, player.direction_d);
		we_ray_cast(&ray, m->tiles);
		we_draw_floor(ray, frame_buffer, &m->textures.floor);
		we_draw_wall(ray, frame_buffer, &m->textures);
		ray.tile_type_to_find = WE_DOOR;
		we_ray_cast(&ray, m->tiles);
		we_draw_door(ray, frame_buffer, &m->textures);
		angle_d += ray.angle_increment_d;
		ray.nb++;
	}
}
