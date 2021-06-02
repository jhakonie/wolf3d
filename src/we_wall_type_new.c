/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_wall_type_new.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:54:55 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/01 14:35:21 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

t_bool	we_wall_type_new(t_wall_type *wall_type)
{
	if (!we_texture_new("data/we_abstract.xpm", &wall_type[0].wall[we_north]))
		return (we_wall_type_del(wall_type, 0, we_north));
	write(1, "\n1/4 loaded\n", 13);
	if (!we_texture_new("data/we_south.xpm", &wall_type[0].wall[we_east]))
		return (we_wall_type_del(wall_type, 0, we_east));
	write(1, "\n2/4 loaded\n", 13);
	if (!we_texture_new("data/we_wave.xpm", &wall_type[0].wall[we_south]))
		return (we_wall_type_del(wall_type, 0, we_south));
	write(1, "\n3/4 loaded\n", 13);
	if (!we_texture_new("data/we_north.xpm", &wall_type[0].wall[we_west]))
		return (we_wall_type_del(wall_type, 0, we_west));
	write(1, "\n4/4 loaded\n", 13);
	if (!we_texture_new("data/we_abstract.xpm", &wall_type[1].wall[0]))
		return (we_wall_type_del(wall_type, 1, 0));
	write(1, "\nfloor texture loaded\n", 13);
	return (wx_true);
}
