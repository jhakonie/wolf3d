/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_ray_cast_check_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:41:30 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/23 11:48:03 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

t_bool	we_ray_cast_check_map(t_item *chart, t_ray *ray, t_u32 line,
								t_u32 index)
{
	ray->chart_index = chart[index].id;
	if (line == WE_VERTICAL)
	{
		ray->compass = 0xffffff;
	}
	else if (line == WE_HORIZONTAL)
	{
		ray->compass = 0xffffff;
	}
	if (chart[index].id == 1 || chart[index].id == 2)
		return (wx_true);
	return (wx_false);
}
