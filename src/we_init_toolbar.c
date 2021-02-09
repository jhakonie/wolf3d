/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_init_toolbar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:21:13 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/08 22:42:11 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"
#include <stdio.h>

void	we_init_tools(t_tools *t, t_u32 win_w, t_u32 win_h)
{
	t->start.x = 0;
	t->start.y = 0;
	t->end.x = (win_w - 1) / 8;
	t->end.y = win_h - 1;
	t->id = WE_ID_INIT;
	we_u32_to_rgba(&t->color[0], 0xe0ffff);
	we_u32_to_rgba(&t->color[1], 0x2e8b57);
	we_init_wall(&t->tool[1], win_w, win_h);
	we_init_floor(&t->tool[2], win_w, win_h);
	we_init_door(&t->tool[0], win_w, win_h);
}

void	we_init_wall(t_tool *t, t_u32 win_w, t_u32 win_h)
{
	t->pre_selected = wx_false;
	t->selected = wx_false;
	t->button.start.x = (win_w - 1) / 35;
	t->button.start.y = win_h / 8;
	t->button.end.x = t->button.start.x + win_w / 12;
	t->button.end.y = t->button.start.y + win_h / 12;
	we_u32_to_rgba(&t->button.color[0], 0xFFFFFF);
	we_u32_to_rgba(&t->button.color[1], 0x00FF00);
	we_u32_to_rgba(&t->button.color[2], 0xFF0000);
	we_u32_to_rgba(&t->button.color[3], 0xcd8500);
}

void	we_init_door(t_tool *t, t_u32 win_w, t_u32 win_h)
{
	t->pre_selected = wx_false;
	t->selected = wx_false;
	t->button.start.x = (win_w - 1) / 35;
	t->button.start.y = win_h / 4;
	t->button.end.x = t->button.start.x + win_w / 12;
	t->button.end.y = t->button.start.y + win_h / 12;
	we_u32_to_rgba(&t->button.color[0], 0xf08080);
	we_u32_to_rgba(&t->button.color[1], 0x00FF00);
	we_u32_to_rgba(&t->button.color[2], 0xFF0000);
	we_u32_to_rgba(&t->button.color[3], 0xcd2626);
}

void	we_init_floor(t_tool *t, t_u32 win_w, t_u32 win_h)
{
	t->pre_selected = wx_false;
	t->selected = wx_false;
	t->button.start.x = (win_w - 1) / 35;
	t->button.start.y = win_h * 3 / 8;
	t->button.end.x = t->button.start.x + win_w / 12;
	t->button.end.y = t->button.start.y + win_h / 12;
	we_u32_to_rgba(&t->button.color[0], 0xffc0cb);
	we_u32_to_rgba(&t->button.color[1], 0x00FF00);
	we_u32_to_rgba(&t->button.color[2], 0xFF0000);
	we_u32_to_rgba(&t->button.color[3], 0xffff00);
}
