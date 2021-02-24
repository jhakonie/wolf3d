/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_from_map_to_win.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 21:00:22 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/24 21:04:40 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

t_p2		we_from_map_to_win(t_p2 map, t_editor *e)
{
	t_p2	win;

	win.x = map.x * e->map.grid.part.x + e->tools.end.x;
	win.y = map.y * e->map.grid.part.y;
	return (win);
}
