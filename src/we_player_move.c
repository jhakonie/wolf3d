/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_player_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:38:08 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/09 18:50:36 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static void	zz_move_forward(t_editor *e, t_f32 s)
{
	t_u32	block;
	t_p2	move;

	move.x = (cosf(e->player.direction_d * WE_TO_RAD) * s
			* e->time.sim_time_step_s);
	move.y = -(sinf(e->player.direction_d * WE_TO_RAD) * s
			* e->time.sim_time_step_s);
	block = (int)((e->player.position.x + move.x) / WE_BLOCK_W)
		+ (int)((e->player.position.y + move.y) / WE_BLOCK_W) *WE_GRID_DIVIDE;
	if (!e->player.wall_collision || (block < WE_MAP_SIZE
			&& (e->map.tiles[block].id == 0 || e->map.tiles[block].id == 3
				|| e->map.tiles[block].id == 2)))
	{
		e->player.move.forward = move;
	}
}

static void	zz_move_backward(t_editor *e, t_f32 s)
{
	t_u32	block;
	t_p2	move;

	move.x = (cosf(e->player.direction_d * WE_TO_RAD) * s
			* e->time.sim_time_step_s);
	move.y = -(sinf(e->player.direction_d * WE_TO_RAD) * s
			* e->time.sim_time_step_s);
	block = (int)((e->player.position.x - move.x) / WE_BLOCK_W)
		+ (int)((e->player.position.y - move.y) / WE_BLOCK_W) *WE_GRID_DIVIDE;
	if (!e->player.wall_collision || (block < WE_MAP_SIZE
			&& (e->map.tiles[block].id == 0 || e->map.tiles[block].id == 3
				|| e->map.tiles[block].id == 2)))
	{
		e->player.move.backward = move;
	}
}

static void	zz_move_right(t_editor *e, t_f32 s)
{
	t_u32	block;
	t_p2	move;

	move.x = cosf((90 + e->player.direction_d) * WE_TO_RAD) * s
		* e->time.sim_time_step_s;
	move.y = -sinf((90 + e->player.direction_d) * WE_TO_RAD) * s
		* e->time.sim_time_step_s;
	block = (int)((e->player.position.x + move.x) / WE_BLOCK_W)
		+ (int)((e->player.position.y + move.y) / WE_BLOCK_W) *WE_GRID_DIVIDE;
	if (!e->player.wall_collision || (block < WE_MAP_SIZE
			&& (e->map.tiles[block].id == 0 || e->map.tiles[block].id == 3
				|| e->map.tiles[block].id == 2)))
	{
		e->player.move.right = move;
	}
}

static void	zz_move_left(t_editor *e, t_f32 s)
{
	t_u32	block;
	t_p2	move;

	move.x = cosf((90 + e->player.direction_d) * WE_TO_RAD) * s
		* e->time.sim_time_step_s;
	move.y = -sinf((90 + e->player.direction_d) * WE_TO_RAD) * s
		* e->time.sim_time_step_s;
	block = (int)((e->player.position.x - move.x) / WE_BLOCK_W)
		+ (int)((e->player.position.y - move.y) / WE_BLOCK_W) *WE_GRID_DIVIDE;
	if (!e->player.wall_collision || (block < WE_MAP_SIZE
			&& (e->map.tiles[block].id == 0 || e->map.tiles[block].id == 3
				|| e->map.tiles[block].id == 2)))
	{
		e->player.move.left = move;
	}
}

void	we_player_move(t_u32 key, t_editor *e)
{
	if (key == SDLK_w)
		zz_move_forward(e, e->player.w_step);
	else if (key == SDLK_a)
		zz_move_right(e, e->player.w_step);
	else if (key == SDLK_s)
		zz_move_backward(e, e->player.w_step);
	else if (key == SDLK_d)
		zz_move_left(e, e->player.w_step);
}
