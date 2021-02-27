/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_editor_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:14:34 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/27 00:40:39 by jhakonie         ###   ########.fr       */
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

t_bool			we_editor_new(t_editor *e, t_u32 window_width,\
	t_u32 window_height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (zz_on_error(e, 0));
	if (!(e->window = SDL_CreateWindow("wolf3d_editor", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, window_width, window_height\
		, SDL_WINDOW_RESIZABLE)))
		return (zz_on_error(e, 1));
	if (!(e->renderer = SDL_CreateRenderer(e->window, -1, 0)))
		return (zz_on_error(e, 2));
	if (!(e->texture = SDL_CreateTexture(e->renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING, window_width, window_height)))
		return (zz_on_error(e, 3));
	if (!wx_frame_buffer_new(&e->frame_buffer, window_width, window_height))
		return (zz_on_error(e, 4));
	wx_buffer_set(&e->tools, sizeof(e->tools), 0);
	if (!we_chart_new(&e->map))
		return (zz_on_error(e, 5));
	we_init_map(&e->map, window_width, window_height);
	we_init_tools(&e->tools, window_width, window_height);
	we_init_chart(&e->map);
	e->quit = wx_false;
	e->draw = wx_true;
	return (wx_true);
}
