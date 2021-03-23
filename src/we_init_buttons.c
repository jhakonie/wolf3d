/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_init_buttons.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:36:40 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/23 13:37:18 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_init_save(t_tool *t, t_u32 win_w, t_u32 win_h)
{
	t->pre_selected = wx_false;
	t->selected = wx_false;
	t->button.start.x = (win_w - 1) / 35;
	t->button.start.y = win_h * 5 / 8;
	t->button.end.x = t->button.start.x + win_w / 12;
	t->button.end.y = t->button.start.y + win_h / 12;
	t->button.color[0] = 0xcd8500;
	t->button.color[1] = 0x00FF00;
	t->button.color[2] = 0xFF0000;
	t->button.color[3] = 0xf08080;
}

void	we_init_wall(t_tool *t, t_u32 win_w, t_u32 win_h)
{
	t->pre_selected = wx_false;
	t->selected = wx_false;
	t->button.start.x = (win_w - 1) / 35;
	t->button.start.y = win_h / 8;
	t->button.end.x = t->button.start.x + win_w / 12;
	t->button.end.y = t->button.start.y + win_h / 12;
	t->button.color[0] = 0xFFFFFF;
	t->button.color[1] = 0x00FF00;
	t->button.color[2] = 0xFF0000;
	t->button.color[3] = 0xcd8500;
}

void	we_init_player_location(t_tool *t, t_u32 win_w, t_u32 win_h)
{
	t->pre_selected = wx_false;
	t->selected = wx_false;
	t->button.start.x = (win_w - 1) / 35;
	t->button.start.y = win_h * 3 / 8;
	t->button.end.x = t->button.start.x + win_w / 12;
	t->button.end.y = t->button.start.y + win_h / 12;
	t->button.color[0] = 0xAAB0FF;
	t->button.color[1] = 0x00FF00;
	t->button.color[2] = 0xFF0000;
	t->button.color[3] = 0xFF2626;
}

void	we_init_floor(t_tool *t, t_u32 win_w, t_u32 win_h)
{
	t->pre_selected = wx_false;
	t->selected = wx_false;
	t->button.start.x = (win_w - 1) / 35;
	t->button.start.y = win_h / 4;
	t->button.end.x = t->button.start.x + win_w / 12;
	t->button.end.y = t->button.start.y + win_h / 12;
	t->button.color[0] = 0xffc0cb;
	t->button.color[1] = 0x00FF00;
	t->button.color[2] = 0xFF0000;
	t->button.color[3] = 0xffff00;
}

void	we_init_empty(t_tool *t, t_u32 win_w, t_u32 win_h)
{
	t->pre_selected = wx_false;
	t->selected = wx_false;
	t->button.start.x = (win_w - 1) / 35;
	t->button.start.y = win_h * 4 / 8;
	t->button.end.x = t->button.start.x + win_w / 12;
	t->button.end.y = t->button.start.y + win_h / 12;
	t->button.color[0] = 0x000000;
	t->button.color[1] = 0x00FF00;
	t->button.color[2] = 0xFF0000;
	t->button.color[3] = 0xffff00;
}
