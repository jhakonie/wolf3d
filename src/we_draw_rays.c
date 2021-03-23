/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 22:34:23 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/23 00:51:32 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_draw_rays(t_ray ray, t_editor *e)
{
	t_p2 end;
	t_p2 start;
	t_p2 temp;

	temp.x = ray.start.x / WE_BLOCK_W;
	temp.y = ray.start.y / WE_BLOCK_W;
	start = we_from_map_to_win(temp, e);
	temp.x = ray.end.x / WE_BLOCK_W;
	temp.y = ray.end.y / WE_BLOCK_W;
	end = we_from_map_to_win(temp, e);
	if (e->map.draw_rays_no_wall == wx_true && (ray.chart_index != 1
		&& ray.chart_index != 2))
		we_draw_line(start, end, &e->frame_buffer, 0x00ff00);
	else if (e->map.draw_rays_wall == wx_true && (ray.chart_index == 1
		|| ray.chart_index == 2))
		we_draw_line(start, end, &e->frame_buffer, 0xff00ff);
}
