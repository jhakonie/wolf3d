/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_shade_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 23:16:10 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/02 10:42:48 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

void	we_shade_pixel(t_u32 *color, t_f32 distance)
{
	t_rgba			new_color;
	t_f32			shade_factor;
	static t_f32	max_dist_w = (WE_GRID_DIVIDE * 0.35f * WE_BLOCK_W);
	t_u32			i;

	i = 0;
	shade_factor = distance / max_dist_w;
	if (shade_factor >= 1)
		shade_factor = 1;
	new_color.r = (((*color & 0x000000FF) >> 0) * (1 - shade_factor));
	new_color.g = (((*color & 0x0000FF00) >> 8) * (1 - shade_factor));
	new_color.b = (((*color & 0x00FF0000) >> 16) * (1 - shade_factor));
	*color = (new_color.b << 16)
		| (new_color.g << 8) | (new_color.r << 0);
}
