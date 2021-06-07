/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 22:34:23 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/07 19:54:17 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_draw_rays(t_ray ray, t_map map, t_frame_buffer *fb)
{
	t_p2	end;
	t_p2	start;
	t_p2	temp;

	if (ray.tile.side != we_no_wall)
	{
		temp.x = ray.start.x / WE_BLOCK_W;
		temp.y = ray.start.y / WE_BLOCK_W;
		start = we_from_map_to_win(temp, map);
		temp.x = ray.tile.hit.x / WE_BLOCK_W;
		temp.y = ray.tile.hit.y / WE_BLOCK_W;
		end = we_from_map_to_win(temp, map);
		if (start.x > map.grid.start.x)
			we_draw_line(start, end, fb, 0x00ff00);
	}
}
