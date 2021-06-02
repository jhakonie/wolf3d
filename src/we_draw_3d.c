/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:10:51 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/02 11:48:06 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_draw_3d(t_frame_buffer *frame_buffer, t_player player,
	t_map map)
{
	t_f32	angle_d;
	t_ray	ray;

	angle_d = 0;
	wx_buffer_set(frame_buffer->data, frame_buffer->data_size, 0);
	wx_buffer_set(&ray, sizeof(t_ray), 0);
	we_ray_init(&ray, player.fov_d, frame_buffer->width, player.position);
	ray.view_height = player.height;
	ray.tile_type_to_find = 1;
	while (ray.nb < frame_buffer->width)
	{
		we_ray_calculate(&ray, angle_d, player.direction_d);
		we_ray_cast(&ray, map.tiles);
		we_draw_floor(ray, frame_buffer, map.wall_type);
		we_draw_wall(ray, frame_buffer, map.wall_type);
		angle_d += ray.angle_increment_d;
		ray.nb++;
	}
}
