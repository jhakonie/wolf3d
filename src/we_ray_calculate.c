/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_ray_calculate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:18:30 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/23 21:18:25 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

/*
** ang_ray_start_d = angle between ray and ray-cast start angle.
**
** ray->angle_d = angle of ray measured counter clock-wise from positive
** x-axis on a left handed coordinate system.
**
** ray_length = distance from ray start to projection plane
**
** ray->k and ray->b are terms of the mathematical formula of a line y = kx + b
**
** ray->delta = the difference in x and y between ray start and ray
** intersection with screen
**
** TODO: check if ray->angle_d - notes are correct (also from ray_init)
*/

void		we_ray_calculate(t_ray *ray, t_f32 ang_ray_start_d,
								t_f32 player_direction_d)
{
	t_f32 ray_length;

	ray->angle_to_player_d = fabsf(ray->half_fov_d - ang_ray_start_d);
	ray->angle_d = player_direction_d + ray->half_fov_d
							- ang_ray_start_d;
	if (ray->angle_d < 0)
		ray->angle_d += 360;
	else if (ray->angle_d > 360)
		ray->angle_d -= 360;
	ray_length = ray->dist_to_screen /
		cos(wx_to_radians(ray->angle_to_player_d));
	ray->delta.x = fabs(cos(wx_to_radians(ray->angle_d))) * ray_length;
	ray->delta.y = fabs(sin(wx_to_radians(ray->angle_d))) * ray_length;
	if (ray->angle_d < 180)
		ray->delta.y *= -1;
	if (ray->angle_d > 90 && ray->angle_d < 270)
		ray->delta.x *= -1;
	if (ray->delta.x == 0)
		ray->k = 0;
	else
		ray->k = ray->delta.y / ray->delta.x;
	ray->b = -ray->k * ray->start.x + ray->start.y;
}
