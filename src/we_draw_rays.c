/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 22:34:23 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/24 15:10:25 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_draw_rays(t_ray ray, t_map map, t_frame_buffer *fb)
{
	t_p2	end;
	t_p2	start;
	t_p2	temp;

	temp.x = ray.start.x / WE_BLOCK_W;
	temp.y = ray.start.y / WE_BLOCK_W;
	start = we_from_map_to_win(temp, map);
	temp.x = ray.wall.end.x / WE_BLOCK_W;
	temp.y = ray.wall.end.y / WE_BLOCK_W;
	end = we_from_map_to_win(temp, map);
	if ((map.draw_rays_no_wall) && (ray.wall.chart_index != 1
			&& ray.wall.chart_index != 2))
		we_draw_line(start, end, fb, 0x00ff00);
	else if ((map.draw_rays_wall) && (ray.wall.chart_index == 1
			|| ray.wall.chart_index == 2))
		we_draw_line(start, end, fb, 0xff00ff);
}
