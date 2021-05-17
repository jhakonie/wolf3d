/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:08:31 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/17 14:36:28 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

void	we_draw_wall(t_ray ray, t_frame_buffer *fb, t_wall_type *wall_type)
{
	t_p2			draw_start;
	t_tex			texture;

	if (ray.wall.tiles_id == 2)
		texture = wall_type[1].wall[ray.wall.compass];
	else
		texture = wall_type[0].wall[ray.wall.compass];
	if (ray.wall.distance > 0)
		ray.wall.projected_height = (ray.dist_to_screen / ray.wall.distance)
			* WE_BLOCK_W;
	draw_start.y = ray.player_height * fb->height
		- ray.player_height * ray.wall.projected_height;
	if ((t_s32)draw_start.y >= (t_s32)fb->height)
		return ;
	draw_start.x = (t_f32)ray.nb;
	we_draw_texture_wall(ray, draw_start, fb, texture);
}
