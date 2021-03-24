/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_player_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:38:08 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/24 15:34:36 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static void	zz_move(t_u32 key, t_editor *e, t_u32 s)
{
	if (key == SDLK_w)
	{
		e->player.position.x += (cos(e->player.direction_d * WE_TO_RAD) * s);
		e->player.position.y += -(sin(e->player.direction_d * WE_TO_RAD) * s);
	}
	else if (key == SDLK_s)
	{
		e->player.position.x -= (cos(e->player.direction_d * WE_TO_RAD) * s);
		e->player.position.y -= -(sin(e->player.direction_d * WE_TO_RAD) * s);
	}
}

static void	zz_move_sideways(t_u32 key, t_editor *e, t_u32 s)
{
	if (key == SDLK_a)
	{
		e->player.position.x += cos((90 + e->player.direction_d) * WE_TO_RAD)
			* s;
		e->player.position.y += -sin((90 + e->player.direction_d) * WE_TO_RAD)
			* s;
	}
	else if (key == SDLK_d)
	{
		e->player.position.x -= cos((90 + e->player.direction_d) * WE_TO_RAD)
			* s;
		e->player.position.y -= -sin((90 + e->player.direction_d) * WE_TO_RAD)
			* s;
	}
}

void	we_player_move(t_u32 key, t_editor *e)
{
	t_u32	s;

	s = e->player.w_step;
	if (key == SDLK_w || key == SDLK_s)
		zz_move(key, e, s);
	else if (key == SDLK_a || key == SDLK_d)
		zz_move_sideways(key, e, s);
}
