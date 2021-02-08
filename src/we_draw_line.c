/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:09:11 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/08 12:21:39 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void		we_draw_line(t_point start, t_point end, t_frame_buffer *fb,
	t_rgba color)
{
	float	dx;
	float	dy;
	float	s;
	float	i;

	i = 0;
	dx = end.x - start.x;
	dy = end.y - start.y;
	if (fabsf(dx) >= fabsf(dy))
		s = fabsf(dx);
	else
		s = fabsf(dy);
	if (s == 0)
		return ;
	dx = dx / s;
	dy = dy / s;
	while (i < s)
	{
		we_draw_pixel(start, fb, color);
		start.x += dx;
		start.y += dy;
		i++;
	}
}
