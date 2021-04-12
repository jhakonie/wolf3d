/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_wall_compass_direction.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 23:56:28 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/30 16:15:40 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

t_compass	we_wall_compass_direction(t_f32 angle_ray_d, t_u32 side)
{
	t_compass	direction;

	if (side == we_horisontal)
	{
		direction = we_north;
		if (angle_ray_d > 180)
			direction = we_south;
	}
	else
	{
		direction = we_east;
		if (angle_ray_d > 90 && angle_ray_d < 270)
			direction = we_west;
	}
	return (direction);
}
