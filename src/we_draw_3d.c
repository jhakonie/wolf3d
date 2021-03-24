/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:10:51 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/24 15:06:35 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static t_u32	zz_wall_color(t_ray ray)
{
	t_u32	color;

	color = 0;
	if (ray.wall.compass == we_north)
		color = 0x00ff00;
	else if (ray.wall.compass == we_west)
		color = 0xfff000;
	else if (ray.wall.compass == we_south)
		color = 0xff00ff;
	else if (ray.wall.compass == we_east)
		color = 0x00ffff;
	return (color);
}

static void	zz_draw_wall_to_buffer(t_ray ray, t_frame_buffer *fb)
{
	t_f32	projected_height;
	t_u32	i;
	t_p2	draw_start;
	t_u32	color;

	i = 0;
	color = 0;
	color = zz_wall_color(ray);
	if (ray.wall.distance > 0)
		projected_height = (ray.dist_to_screen / ray.wall.distance)
			* WE_BLOCK_W;
	else
		return ;
	draw_start.y = 0.5 * fb->height - 0.5 * projected_height;
	if ((int)draw_start.y < 0)
		draw_start.y = 0;
	draw_start.x = (t_f32)ray.nb;
	while (i < (t_u32)projected_height)
	{
		we_draw_pixel(draw_start, fb, color);
		draw_start.y++;
		i++;
	}
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
