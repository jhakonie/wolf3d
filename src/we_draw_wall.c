/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:08:31 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 23:28:38 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

static t_tex	zz_choose_texture(t_ray ray, t_wall_type *wall_type, t_u32 id)
{
	if (ray.wall.compass == we_north)
		return (wall_type[id].wall[we_north]);
	else if (ray.wall.compass == we_east)
		return (wall_type[id].wall[we_east]);
	else if (ray.wall.compass == we_south)
		return (wall_type[id].wall[we_south]);
	return (wall_type[id].wall[we_west]);
}

void	we_draw_wall(t_ray ray, t_frame_buffer *fb, t_wall_type *wall_type)
{
	t_p2			draw_start;
	t_tex			texture;

	if (ray.wall.chart_id == 2)
		texture = zz_choose_texture(ray, wall_type, 1);
	else
		texture = zz_choose_texture(ray, wall_type, 0);
	if (ray.wall.distance > 0)
		ray.wall.projected_height = (ray.dist_to_screen / ray.wall.distance)
			* WE_BLOCK_W;
	draw_start.y = 0.5 * fb->height - 0.5 * ray.wall.projected_height;
	if ((t_s32)draw_start.y < 0)
		draw_start.y = 0;
	draw_start.x = (t_f32)ray.nb;
	we_draw_texture_wall(ray, draw_start, fb, texture);
}
