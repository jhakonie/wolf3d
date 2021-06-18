/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:08:31 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/17 01:30:16 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

void	we_draw_wall(t_ray ray, t_frame_buffer *fb,
			t_map_textures *textures)
{
	t_p2			draw_start;
	t_texture		texture;

	if (ray.tile.tiles_id == 1)
		texture = textures->walls[ray.tile.compass];
	else
		return ;
	draw_start.y = ray.view_height * fb->height
		- ray.view_height * ray.tile.projected_height;
	if ((t_s32)draw_start.y >= (t_s32)fb->height)
		return ;
	draw_start.x = (t_f32)ray.nb;
	we_draw_texture_wall(&ray, draw_start, fb, &texture);
}
