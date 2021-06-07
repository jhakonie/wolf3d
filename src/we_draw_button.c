/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_button.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 22:59:59 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/08 01:24:12 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_draw_button(t_tool *t, t_frame_buffer *fb)
{
	if (!t->pre_selected && !t->selected)
	{
		we_draw_rec_texture(t->button.start, t->button.end, fb,
			&t->button.icon);
	}
	else if (t->pre_selected && !t->selected)
	{
		we_draw_rec_full(t->button.start, t->button.end, fb,
			t->button.color[0]);
	}
	else if (t->selected)
	{
		we_draw_rec_full(t->button.start, t->button.end, fb,
			t->button.color[1]);
	}
	we_draw_rec_frame(t->button.start, t->button.end, fb,
		t->button.color[2]);
}
