/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_toolbar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 00:21:04 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/08 17:16:58 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_draw_toolbar(t_editor *e)
{
	t_u32 i;

	i = 0;
	we_draw_rec_full(e->tools.start, e->tools.end, &e->frame_buffer,
	e->tools.color[0]);
	we_draw_rec_frame(e->tools.start, e->tools.end, &e->frame_buffer,
	e->tools.color[1]);
	while (i < 3)
	{
		we_draw_button(&e->tools.tool[i], &e->frame_buffer);
		i++;
	}
	e->draw = wx_false;
}
