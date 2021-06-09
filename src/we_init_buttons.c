/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_init_buttons.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:36:40 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/09 20:18:13 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_init_save(t_tool *t, t_u32 win_w, t_u32 win_h)
{
	t->pre_selected = wx_false;
	t->selected = wx_false;
	t->button.start.x = (win_w - 1) / 45;
	t->button.start.y = win_h * 5 / 8;
	t->button.end.x = t->button.start.x + win_w / 12;
	t->button.end.y = t->button.start.y + win_h / 12;
}

void	we_init_wall(t_tool *t, t_u32 win_w, t_u32 win_h)
{
	t->pre_selected = wx_false;
	t->selected = wx_false;
	t->button.start.x = (win_w - 1) / 45;
	t->button.start.y = win_h / 8;
	t->button.end.x = t->button.start.x + win_w / 12;
	t->button.end.y = t->button.start.y + win_h / 12;
}

void	we_init_player_location(t_tool *t, t_u32 win_w, t_u32 win_h)
{
	t->pre_selected = wx_false;
	t->selected = wx_false;
	t->button.start.x = (win_w - 1) / 45;
	t->button.start.y = win_h * 3 / 8;
	t->button.end.x = t->button.start.x + win_w / 12;
	t->button.end.y = t->button.start.y + win_h / 12;
}

void	we_init_door(t_tool *t, t_u32 win_w, t_u32 win_h)
{
	t->pre_selected = wx_false;
	t->selected = wx_false;
	t->button.start.x = (win_w - 1) / 45;
	t->button.start.y = win_h / 4;
	t->button.end.x = t->button.start.x + win_w / 12;
	t->button.end.y = t->button.start.y + win_h / 12;
}

void	we_init_empty(t_tool *t, t_u32 win_w, t_u32 win_h)
{
	t->pre_selected = wx_false;
	t->selected = wx_false;
	t->button.start.x = (win_w - 1) / 45;
	t->button.start.y = win_h * 4 / 8;
	t->button.end.x = t->button.start.x + win_w / 12;
	t->button.end.y = t->button.start.y + win_h / 12;
}
