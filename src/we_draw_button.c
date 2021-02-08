/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_button.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 22:59:59 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/08 12:28:29 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_draw_button(t_editor *e)
{
	if (!e->tool.pre_selected && !e->tool.selected)
		we_draw_rec_full(e->tool.button.start, e->tool.button.end,
		&e->frame_buffer, e->tool.button.color[0]);
	else if (e->tool.pre_selected && !e->tool.selected)
		we_draw_rec_full(e->tool.button.start, e->tool.button.end,
		&e->frame_buffer, e->tool.button.color[1]);
	else if (e->tool.selected)
		we_draw_rec_full(e->tool.button.start, e->tool.button.end,
		&e->frame_buffer, e->tool.button.color[2]);
	we_draw_rec_frame(e->tool.button.start, e->tool.button.end,
		&e->frame_buffer, e->tool.button.color[3]);
	e->draw = wx_false;
}
