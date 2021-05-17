/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_ray_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:04:17 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/15 00:40:09 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

/*
** ray->angle_to_player_d = angle between player and ray.
**
** ray->nb = ray number startting from the start of screen.
**
** ray->angle_d = angle of ray measured counter clock-wise from positive
** x-axis on a left handed coordinate system.
**
** ray->k and ray->b form y = kx + b.
**
** ray->delta = ray_intersection_with_screen(x, y) - ray_start(x, y).
*/

void	we_ray_init(t_ray *ray, t_f32 player_fov_d, t_f32 screen_width,
	t_p2 player_position)
{
	static t_f32	map_side_w = WE_GRID_DIVIDE * WE_BLOCK_W;
	t_f32			pow_map_side_w;

	pow_map_side_w = map_side_w * map_side_w;
	ray->max_distance_w = sqrtf(pow_map_side_w + pow_map_side_w);
	ray->nb = 0;
	ray->k = 0;
	ray->b = 0;
	ray->angle_d = 0;
	ray->angle_to_player_d = 0;
	ray->delta.x = 0;
	ray->delta.y = 0;
	wx_buffer_set(&ray->wall, sizeof(ray->wall), 0);
	ray->half_fov_d = player_fov_d * 0.5f;
	ray->start = player_position;
	ray->angle_increment_d = player_fov_d / screen_width;
}
