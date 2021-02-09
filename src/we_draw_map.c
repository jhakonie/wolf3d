/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:52:54 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/09 15:32:00 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void		we_draw_map(t_editor *e)
{
	t_u32	i;

	i = 0;
	while (i < e->map.block_count - 1)
	{
		if (e->map.chart[i].id != WE_ID_INIT)
		{
			e->map.old_block.x = e->tools.start.x + e->map.grid.part.x *
				e->map.chart[i].loc.x;
			e->map.old_block.y = e->map.grid.part.y * e->map.chart[i].loc.y;
			we_draw_block(e, e->map.chart[i].id);
		}
		i++;
	}
	e->map.old_block_draw = wx_false;
}
