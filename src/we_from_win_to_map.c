/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_from_win_to_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 21:12:26 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/27 13:22:01 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

t_p2		we_from_win_to_map(t_p2 win, t_editor *e)
{
	t_p2	map;
	t_p2	low;

	low.x = e->tools.end.x;
	low.y = 0;
	while (low.x < win.x)
		low.x += e->map.grid.part.x;
	low.x -= e->map.grid.part.x;
	map.x = (low.x - e->tools.end.x) / e->map.grid.part.x;
	while (low.y < win.y)
		low.y += e->map.grid.part.y;
	low.y -= e->map.grid.part.y;
	map.y = low.y / e->map.grid.part.y;
	return (map);
}
