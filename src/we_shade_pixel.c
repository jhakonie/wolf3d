/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_shade_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 23:16:10 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 19:52:39 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

void	we_shade_pixel(t_ray ray, t_u32 *color, t_f32 darkness)
{
	t_rgba			new_color;
	t_f32			shade_factor;
	t_u32			i;

	i = 0;
	shade_factor = ray.wall.distance / ray.max_distance_w;
	while (i < darkness)
	{
		new_color.a = (((*color & 0x000000FF) >> 0) * (1 - shade_factor));
		new_color.b = (((*color & 0x0000FF00) >> 8) * (1 - shade_factor));
		new_color.g = (((*color & 0x00FF0000) >> 16) * (1 - shade_factor));
		new_color.r = (((*color & 0xFF000000) >> 24) * (1 - shade_factor));
		*color = (new_color.r << 24) | (new_color.g << 16)
			| (new_color.b << 8) | (new_color.a << 0);
		i++;
	}
}
