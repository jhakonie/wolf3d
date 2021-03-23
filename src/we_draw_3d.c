/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:10:51 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/23 13:31:19 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static void		zz_draw_wall_to_buffer(t_ray ray, t_frame_buffer *fb)
{
	t_f32	projected_height;
	t_u32	i;
	t_p2	draw_start;
	t_u32	color;

	i = 0;
	color = ray.compass;
	if (ray.dist_to_wall > 0)
		projected_height = (ray.dist_to_screen /
			ray.dist_to_wall) * WE_BLOCK_W;
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

/*
** ang_ray_start_d = angle between ray and ray cast start angle
*/

static void		zz_ray_calculate(t_ray *ray, t_f32 ang_ray_start_d,
								t_f32 player_direction_d)
{
	t_f32 ray_length;
	t_f32 ang_ray_direction_d;

	ray->angle_to_player_d = fabsf(ray->half_fov_d - ang_ray_start_d);
	ang_ray_direction_d = player_direction_d + ray->half_fov_d
							- ang_ray_start_d;
	if (ang_ray_direction_d < 0)
		ang_ray_direction_d += 360;
	else if (ang_ray_direction_d > 360)
		ang_ray_direction_d -= 360;
	ray->angle_d = ang_ray_direction_d;
	ray_length = ray->dist_to_screen /
		cos(wx_to_radians(ray->angle_to_player_d));
	ray->delta.x = fabs(cos(wx_to_radians(ang_ray_direction_d))) * ray_length;
	ray->delta.y = fabs(sin(wx_to_radians(ang_ray_direction_d))) * ray_length;
	if (ang_ray_direction_d < 180)
		ray->delta.y *= -1;
	if (ang_ray_direction_d > 90 && ang_ray_direction_d < 270)
		ray->delta.x *= -1;
	ray->k = ray->delta.y / ray->delta.x;
	ray->b = -ray->k * ray->start.x + ray->start.y;
}

static void		zz_ray_init(t_ray *ray, t_f32 player_fov_d, t_f32 screen_width,
							t_p2 player_position)
{
	ray->nb = 0;
	ray->compass = 0;
	ray->chart_index = 0;
	ray->start = player_position;
	ray->half_fov_d = player_fov_d * 0.5f;
	ray->dist_to_screen = 0.5f * screen_width /
		tan(wx_to_radians(ray->half_fov_d));
	ray->angle_increment_d = player_fov_d / screen_width;
}

void			we_draw_3d(t_editor *e)
{
	t_f32	angle_d;
	t_ray	ray;

	angle_d = 0;
	if (e->draw_3d == wx_true)
		wx_buffer_set(e->frame_buffer.data, e->frame_buffer.data_size, 0);
	wx_buffer_set(&ray, sizeof(ray), 0);
	zz_ray_init(&ray, e->player.fov_d, e->frame_buffer.width,
				e->player.position);
	while (ray.nb < e->frame_buffer.width)
	{
		zz_ray_calculate(&ray, angle_d, e->player.direction_d);
		we_ray_cast(&ray, e->map.chart);
		if (e->draw_3d == wx_true)
			zz_draw_wall_to_buffer(ray, &e->frame_buffer);
		else if ((e->map.draw_rays))
			we_draw_rays(ray, e);
		angle_d += ray.angle_increment_d;
		ray.nb++;
	}
}
