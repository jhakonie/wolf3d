/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_block.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 22:24:46 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/09 15:54:35 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	zz_init_counters(t_point *draw_map, t_point *count, t_editor e)
{
	if (!e.map.old_block_draw)
	{
		draw_map->x = e.map.new_block.x;
		draw_map->y = e.map.new_block.y;
	}
	else
	{
		draw_map->x = e.map.old_block.x;
		draw_map->y = e.map.old_block.y;
	}
	count->x = 3.0;
	count->y = 1.0;
}

void	zz_find_limits(t_point *top, t_point *low, t_point *count, t_editor *e)
{
	t_point draw_map;

	zz_init_counters(&draw_map, count, *e);
	low->x = e->tools.end.x;
	while (low->x < draw_map.x)
	{
		low->x += e->map.grid.part.x;
		count->x++;
	}
	low->x -= e->map.grid.part.x;
	top->x = low->x + e->map.grid.part.x;
	low->y = 0.0;
	while (low->y < draw_map.y)
	{
		low->y += e->map.grid.part.y;
		count->y++;
	}
	low->y -= e->map.grid.part.y;
	top->y = low->y + e->map.grid.part.y;
	count->y--;
}

void	we_draw_block(t_editor *e, t_u32 id)
{
	t_point	top;
	t_point	low;
	t_point	end;
	t_point	count;
	t_rgba	color;

	zz_find_limits(&top, &low, &count, e);
	if (!e->map.old_block_draw)
	{
		e->map.chart[count.x + count.y * WE_GRID_DIVIDE].loc.x = count.x;
		e->map.chart[count.x + count.y * WE_GRID_DIVIDE].loc.y = count.y;
		e->map.chart[count.x + count.y * WE_GRID_DIVIDE].id = e->tools.id;
	}
	color = e->tools.tool[id].button.color[0];
	end.x = top.x;
	end.y = low.y;
	while (low.y <= top.y)
	{
		we_draw_line(low, end, &e->frame_buffer, color);
		low.y++;
		end.y++;
	}
}
