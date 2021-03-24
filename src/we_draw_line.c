/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:09:11 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/24 15:08:48 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_draw_line(t_p2 start, t_p2 end, t_frame_buffer *fb, t_u32 color)
{
	t_f32	dx;
	t_f32	dy;
	t_f32	s;
	t_f32	i;

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
	while (i <= s)
	{
		start.x = start.x;
		start.y = start.y;
		we_draw_pixel(start, fb, color);
		start.x += dx;
		start.y += dy;
		i++;
	}
}
