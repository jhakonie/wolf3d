/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_save_win_to_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:11:52 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/27 13:20:51 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void		we_save_win_to_map(t_p2 win, t_editor *e)
{
	t_u32	block_num;
	t_p2	map;

	map = we_from_win_to_map(win, e);
	if (map.x < WE_GRID_DIVIDE && map.y < WE_GRID_DIVIDE)
	{
		block_num = (int)map.x + WE_GRID_DIVIDE * (int)map.y;
		e->map.chart[block_num].block.x = map.x;
		e->map.chart[block_num].block.y = map.y;
		e->map.chart[block_num].id = e->tools.id;
	}
}
