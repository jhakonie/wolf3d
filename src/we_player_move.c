/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_player_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:38:08 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/17 15:30:34 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static void	zz_move_forward(t_editor *e, t_f32 s)
{
	t_u32	block;
	t_p2	move;

	move.x = (cos(e->player.direction_d * WE_TO_RAD) * s);
	move.y = -(sin(e->player.direction_d * WE_TO_RAD) * s);
	block = (int)((e->player.position.x + move.x) / WE_BLOCK_W)
		+ (int)((e->player.position.y + move.y) / WE_BLOCK_W) *WE_GRID_DIVIDE;
	if (e->map.tiles[block].id == 0 || e->map.tiles[block].id == 3
		|| !e->player.wall_collision)
	{
		e->player.position.x += move.x;
		e->player.position.y += move.y;
	}
}

static void	zz_move_backward(t_editor *e, t_f32 s)
{
	t_u32	block;
	t_p2	move;

	move.x = (cos(e->player.direction_d * WE_TO_RAD) * s);
	move.y = -(sin(e->player.direction_d * WE_TO_RAD) * s);
	block = (int)((e->player.position.x - move.x) / WE_BLOCK_W)
		+ (int)((e->player.position.y - move.y) / WE_BLOCK_W) *WE_GRID_DIVIDE;
	if (e->map.tiles[block].id == 0 || e->map.tiles[block].id == 3
		|| !e->player.wall_collision)
	{
		e->player.position.x -= move.x;
		e->player.position.y -= move.y;
	}
}

static void	zz_move_right(t_editor *e, t_f32 s)
{
	t_u32	block;
	t_p2	move;

	move.x = cos((90 + e->player.direction_d) * WE_TO_RAD) * s;
	move.y = -sin((90 + e->player.direction_d) * WE_TO_RAD) * s;
	block = (int)((e->player.position.x + move.x) / WE_BLOCK_W)
		+ (int)((e->player.position.y + move.y) / WE_BLOCK_W) *WE_GRID_DIVIDE;
	if (e->map.tiles[block].id == 0 || e->map.tiles[block].id == 3
		|| !e->player.wall_collision)
	{
		e->player.position.x += move.x;
		e->player.position.y += move.y;
	}
}

static void	zz_move_left(t_editor *e, t_f32 s)
{
	t_u32	block;
	t_p2	move;

	move.x = cos((90 + e->player.direction_d) * WE_TO_RAD) * s;
	move.y = -sin((90 + e->player.direction_d) * WE_TO_RAD) * s;
	block = (int)((e->player.position.x - move.x) / WE_BLOCK_W)
		+ (int)((e->player.position.y - move.y) / WE_BLOCK_W) *WE_GRID_DIVIDE;
	if (e->map.tiles[block].id == 0 || e->map.tiles[block].id == 3
		|| !e->player.wall_collision)
	{
		e->player.position.x -= move.x;
		e->player.position.y -= move.y;
	}
}

void	we_player_move(t_u32 key, t_editor *e)
{
	if (key == SDLK_w)
		zz_move_forward(e, e->player.w_step);
	else if (key == SDLK_s)
		zz_move_backward(e, e->player.w_step);
	else if (key == SDLK_a)
		zz_move_right(e, e->player.w_step);
	else if (key == SDLK_d)
		zz_move_left(e, e->player.w_step);
}
