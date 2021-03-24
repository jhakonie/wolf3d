/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_from_map_to_win.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 21:00:22 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/24 15:21:29 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

t_p2	we_from_map_to_win(t_p2 map, t_map m)
{
	t_p2	win;

	win.x = (int)(map.x * m.grid.part.x + m.grid.start.x);
	win.y = (int)(map.y * m.grid.part.y);
	return (win);
}
