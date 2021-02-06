/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_rec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:44:05 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/06 13:30:23 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void		we_draw_rec_frame(t_point start, t_point end, t_u8 *data, t_rgba c)
{
	t_point up;
	t_point down;

	up.x = end.x;
	up.y = start.y;
	down.x = start.x;
	down.y = end.y;
	we_draw_line(start, up, data, c);
	we_draw_line(start, down, data, c);
	we_draw_line(up, end, data, c);
	we_draw_line(down, end, data, c);
}

void		we_draw_rec_full(t_point start, t_point end, t_u8 *data, t_rgba c)
{
	t_u32	temp_x;

	temp_x = start.x;
	while (start.y < end.y)
	{
		start.x = temp_x;
		while (start.x < end.x)
		{
			we_draw_pixel(start, data, c);
			start.x++;
		}
		start.y++;
	}
}
