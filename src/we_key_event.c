/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_key_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:36:54 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/17 01:21:38 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static void	zz_go_through_walls(t_bool *wall_collision)
{
	if (!*wall_collision)
		*wall_collision = wx_true;
	else
		*wall_collision = wx_false;
}

static void	zz_change_view(t_bool *draw_3d)
{
	if (!*draw_3d)
		*draw_3d = wx_true;
	else
		*draw_3d = wx_false;
}

static void	zz_player_rotation(t_u32 key, t_f32 *player_direction_d)
{
	if (key == SDLK_LEFT)
	{
		*player_direction_d += 5.0;
		if (*player_direction_d > 360.0)
			*player_direction_d -= 360.0;
	}
	if (key == SDLK_RIGHT)
	{
		*player_direction_d -= 5.0;
		if (*player_direction_d < 0.0)
			*player_direction_d += 360.0;
	}
}

static void	zz_draw_rays_2d(t_bool *draw_rays)
{
	if (!*draw_rays)
		*draw_rays = wx_true;
	else
		*draw_rays = wx_false;
}

void	we_key_event(t_u32 key, t_editor *e)
{
	if (key == SDLK_SPACE)
		zz_change_view(&e->map_view.draw_3d);
	else if (key == SDLK_LEFT || key == SDLK_RIGHT)
		zz_player_rotation(key, &e->player.direction_d);
	else if (key == SDLK_w || key == SDLK_a || key == SDLK_s || key == SDLK_d)
		we_player_move(key, e);
	else if (key == SDLK_r)
		zz_draw_rays_2d(&e->map_view.draw_rays);
	else if (key == SDLK_c)
		zz_go_through_walls(&e->player.wall_collision);
	else if (key == SDLK_f && !e->player.run)
	{
		e->player.run = wx_true;
		e->player.w_step *= 2;
	}
	else if (key == SDLK_f && e->player.run)
	{
		e->player.run = wx_false;
		e->player.w_step *= 0.5;
	}
	e->draw = wx_true;
}
