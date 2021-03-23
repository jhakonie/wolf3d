/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_from_win_to_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 21:12:26 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/19 20:33:52 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

t_p2		we_from_win_to_map(t_p2 win, t_editor *e)
{
	t_p2	map;

	map.x = (int)((win.x - e->tools.end.x) / e->map.grid.part.x);
	map.y = (int)(win.y / e->map.grid.part.y);
	return (map);
}
