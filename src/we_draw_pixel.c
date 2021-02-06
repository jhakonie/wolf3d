/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:25:21 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/03 21:27:46 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void		we_u32_to_rgba(t_rgba *color, t_u32 color_int)
{
	color->a = (color_int >> 24);
	color->b = (color_int) & 0xFF;
	color->g = (color_int >> 8) & 0xFF;
	color->r = (color_int >> 16) & 0xFF;
}

void		we_draw_pixel(t_point point, t_u8 *data, t_rgba color)
{
	data[0 + ((int)point.x + WIN_W * (int)point.y) * 4] = color.a;
	data[1 + ((int)point.x + WIN_W * (int)point.y) * 4] = color.b;
	data[2 + ((int)point.x + WIN_W * (int)point.y) * 4] = color.g;
	data[3 + ((int)point.x + WIN_W * (int)point.y) * 4] = color.r;
}
