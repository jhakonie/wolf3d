/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_key_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:36:54 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/24 15:28:03 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

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
		*player_direction_d += 1.0;
		if (*player_direction_d > 360.0)
			*player_direction_d -= 360.0;
	}
	if (key == SDLK_RIGHT)
	{
		*player_direction_d -= 1.0;
		if (*player_direction_d < 0.0)
			*player_direction_d += 360.0;
	}
}

static void	zz_draw_rays_2d(t_u32 key, t_editor *e)
{
	if (key == SDLK_r)
	{
		if (!e->map.draw_rays)
			e->map.draw_rays = wx_true;
		else
			e->map.draw_rays = wx_false;
	}
	if (key == SDLK_t)
	{
		if (!e->map.draw_rays_wall)
			e->map.draw_rays_wall = wx_true;
		else
			e->map.draw_rays_wall = wx_false;
	}
	if (key == SDLK_y)
	{
		if (!e->map.draw_rays_no_wall)
			e->map.draw_rays_no_wall = wx_true;
		else
			e->map.draw_rays_no_wall = wx_false;
	}
}

void	we_key_event(t_u32 key, t_editor *e)
{
	if (key == SDLK_SPACE)
		zz_change_view(&e->map.draw_3d);
	else if (key == SDLK_LEFT || key == SDLK_RIGHT)
		zz_player_rotation(key, &e->player.direction_d);
	else if (key == SDLK_w || key == SDLK_s || key == SDLK_a || key == SDLK_d)
		we_player_move(key, e);
	else if (key == SDLK_r || key == SDLK_t || key == SDLK_y)
		zz_draw_rays_2d(key, e);
	e->draw = wx_true;
}
