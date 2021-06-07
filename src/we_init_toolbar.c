/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_init_toolbar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:21:13 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/07 22:58:54 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_init_toolbar(t_tools *t, t_u32 win_w, t_u32 win_h)
{
	t->start.x = 0;
	t->start.y = 0;
	t->end.x = (win_w - 1) / 8;
	t->end.y = win_h - 1;
	t->id = WE_ID_INIT;
	wx_buffer_set(&t->tool[0], sizeof(t_tool), 0);
	t->color[0] = 0xe0ffff;
	t->color[1] = 0x2e8b57;
	we_init_wall(&t->tool[1], win_w, win_h);
	we_init_floor(&t->tool[2], win_w, win_h);
	we_init_player_location(&t->tool[3], win_w, win_h);
	we_init_empty(&t->tool[4], win_w, win_h);
	we_init_save(&t->tool[5], win_w, win_h);
}
