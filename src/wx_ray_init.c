/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_ray_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:04:17 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/19 20:25:03 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_draw.h"

/*
** ray->nb = ray number startting from the start of screen.
**
** ray->k and ray->b from "y = kx + b".
**
** ray->angle_d = angle of ray measured counter clock-wise from positive
**
** ray->angle_to_player_d = angle between player and ray.
**
** (x-axis on a left handed coordinate system)
*/

void	wx_ray_init(t_ray *ray, t_f32 player_fov_d, t_f32 screen_width,
	t_p2 player_position)
{
	ray->nb = 0;
	ray->k = 0;
	ray->b = 0;
	ray->angle_d = 0;
	ray->angle_to_player_d = 0;
	wx_buffer_set(&ray->tile, sizeof(ray->tile), 0);
	ray->half_fov_d = player_fov_d * 0.5f;
	ray->start = player_position;
	ray->dist_to_screen_w = 0.5f * screen_width
		/ tanf(wx_to_radians(0.5f * player_fov_d));
	ray->angle_increment_d = player_fov_d / screen_width;
	ray->world_end_w = WX_MAP_TILES_WIDTH * WX_TILE_WIDTH;
}
