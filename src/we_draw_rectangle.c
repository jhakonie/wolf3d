/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_rec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:44:05 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/24 20:25:28 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void		we_draw_rec_frame(t_p2 start, t_p2 end, t_frame_buffer *fb,
				t_rgba c)
{
	t_p2 up;
	t_p2 down;

	up.x = end.x;
	up.y = start.y;
	down.x = start.x;
	down.y = end.y;
	we_draw_line(start, up, fb, c);
	we_draw_line(start, down, fb, c);
	we_draw_line(up, end, fb, c);
	we_draw_line(down, end, fb, c);
}

void		we_draw_rec_full(t_p2 start, t_p2 end, t_frame_buffer *fb,
				t_rgba c)
{
	t_f32	temp_x;

	temp_x = start.x;
	while (start.y < end.y)
	{
		start.x = temp_x;
		while (start.x < end.x)
		{
			we_draw_pixel(start, fb, c);
			start.x++;
		}
		start.y++;
	}
}
