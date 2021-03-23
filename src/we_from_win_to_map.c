/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_from_win_to_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 21:12:26 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/23 18:56:50 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

t_p2		we_from_win_to_map(t_p2 win, t_map m)
{
	t_p2	map;

	map.x = (int)((win.x - m.grid.start.x) / m.grid.part.x);
	map.y = (int)(win.y / m.grid.part.y);
	return (map);
}
