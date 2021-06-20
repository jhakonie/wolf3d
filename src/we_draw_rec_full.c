/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_rec_full.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:44:05 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/19 20:12:06 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_draw_rec_full(t_p2 start, t_p2 end, t_frame_buffer *fb, t_u32 c)
{
	t_f32	temp_x;

	if (start.x >= fb->width)
		return ;
	if (start.y < 0)
		start.y = 0;
	if (start.x < 0)
		start.x = 0;
	if (end.x >= fb->width)
		end.x = fb->width - 1;
	if (end.y >= fb->height)
		end.y = fb->height - 1;
	temp_x = start.x;
	while (start.y <= end.y)
	{
		start.x = temp_x;
		while (start.x <= end.x)
		{
			wx_draw_pixel(start, fb, c);
			start.x++;
		}
		start.y++;
	}
}
