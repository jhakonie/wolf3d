/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_wall_type_new.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:54:55 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/10 18:47:54 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

t_bool	we_wall_type_new(t_wall_type *wall_type)
{
	if (!we_texture_new("data/test_letter.xpm", &wall_type[0].wall[we_north]))
		return (we_wall_type_del(wall_type, 0, we_north));
	write(1, "\n1/4 loaded\n", 13);
	if (!we_texture_new("data/test_letter.xpm", &wall_type[0].wall[we_east]))
		return (we_wall_type_del(wall_type, 0, we_east));
	write(1, "\n2/4 loaded\n", 13);
	if (!we_texture_new("data/test_letter.xpm", &wall_type[0].wall[we_west]))
		return (we_wall_type_del(wall_type, 0, we_south));
	write(1, "\n3/4 loaded\n", 13);
	if (!we_texture_new("data/test_letter.xpm", &wall_type[0].wall[we_south]))
		return (we_wall_type_del(wall_type, 0, we_west));
	write(1, "\n4/4 loaded\n", 13);
	return (wx_true);
}
