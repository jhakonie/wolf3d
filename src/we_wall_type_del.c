/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_wall_type_del.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:01:52 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 20:19:12 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

t_bool	we_wall_type_del(t_wall_type *wall_type, t_u32 wall_type_index,
	t_u32 wall_index)
{
	t_u32	i;
	t_u32	j;

	i = 0;
	while (i < wall_type_index)
	{
		j = 0;
		while (j < wall_index)
		{
			free(&wall_type[wall_type_index].wall[wall_index].texture);
			wall_type[wall_type_index].wall[wall_index].texture = WX_NULL;
			j++;
		}
		i++;
	}
	return (wx_false);
}
