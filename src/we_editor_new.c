/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_editor_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:14:34 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/17 16:58:40 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static t_bool	zz_on_error(t_editor *e, t_u8 i)
{
	if (i > 4)
	{
		wx_frame_buffer_del(&e->frame_buffer);
	}
	if (i > 3)
	{
		SDL_DestroyTexture(e->texture);
	}
	if (i > 2)
	{
		SDL_DestroyRenderer(e->renderer);
	}
	if (i > 1)
	{
		SDL_DestroyWindow(e->window);
	}
	if (i > 0)
	{
		SDL_Quit();
	}
	return (wx_false);
}

static t_bool	zz_sdl(t_editor *e, t_u32 window_width, t_u32 window_height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (zz_on_error(e, 0));
	e->window = SDL_CreateWindow("wolf3d_editor", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, window_width, window_height,
			SDL_WINDOW_RESIZABLE);
	if (!e->window)
		return (zz_on_error(e, 1));
	e->renderer = SDL_CreateRenderer(e->window, -1, 0);
	if (!(e->renderer))
		return (zz_on_error(e, 2));
	e->texture = SDL_CreateTexture(e->renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
	if (!e->texture)
		return (zz_on_error(e, 3));
	return (wx_true);
}

t_bool	we_editor_new(t_editor *e, t_u32 window_width, t_u32 window_height)
{
	if (!zz_sdl(e, window_width, window_height))
		return (wx_false);
	if (!wx_frame_buffer_new(&e->frame_buffer, window_width, window_height))
		return (zz_on_error(e, 4));
	wx_buffer_set(&e->tools, sizeof(e->tools), 0);
	if (!we_wall_type_new(e->map.wall_type))
		return (zz_on_error(e, 5));
	we_init_map(&e->map, window_width, window_height);
	we_init_tiles(&e->map);
	we_init_tools(&e->tools, window_width, window_height);
	we_init_player(&e->player, &e->map, e->frame_buffer.width);
	e->quit = wx_false;
	e->draw = wx_true;
	e->map.draw_3d = wx_false;
	return (wx_true);
}
