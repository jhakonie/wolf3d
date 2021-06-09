/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_ray_calculate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:18:30 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/09 15:13:13 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

/*
** ang_ray_start_d = angle between ray and ray-cast start angle.
**
** ray->angle_d = angle of ray measured counter clock-wise from positive
** x-axis on a left handed coordinate system.
**
** ray_length = distance from ray start to projection plane.
**
** ray->k and ray->b form y = kx + b.
**
** ray->delta = ray intersection with projection plane(x,y) - ray_start(x,y).
**	
**		ray_start(x,y)
**			* __ __ __ __ __ __ x
**			|\
**			| \		y = kx + b
**			|  \  /
**	delta.y	|   \/
**			|	 \
**			|delta.x
**			|______\
**			|	    * projection_plane(x,y)
**			|	     \
**			|		  \
**			|		   \
**			y		 	*
**					wall(x,y)
**
** k = delta.y / delta.x
** angle_d ~ 315 degrees
*/

void	we_ray_calculate(t_ray *ray, t_f32 ang_ray_start_d,
	t_f32 player_direction_d)
{
	t_f32	ray_length;
	t_p2	delta;

	ray->angle_to_player_d = fabsf(ray->half_fov_d - ang_ray_start_d);
	ray->angle_d = player_direction_d + ray->half_fov_d - ang_ray_start_d;
	if (ray->angle_d < 0)
		ray->angle_d += 360;
	else if (ray->angle_d > 360)
		ray->angle_d -= 360;
	ray_length = ray->dist_to_screen_w
		/ cosf(wx_to_radians(ray->angle_to_player_d));
	delta.y = fabsf(sinf(wx_to_radians(ray->angle_d))) * ray_length;
	delta.x = fabsf(cosf(wx_to_radians(ray->angle_d))) * ray_length;
	if (ray->angle_d < 180)
		delta.y *= -1;
	if (ray->angle_d > 90 && ray->angle_d < 270)
		delta.x *= -1;
	if (delta.x == 0)
		ray->k = 0;
	else
		ray->k = delta.y / delta.x;
	ray->b = -ray->k * ray->start.x + ray->start.y;
}
