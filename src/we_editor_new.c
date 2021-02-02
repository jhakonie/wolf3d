/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_editor_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:14:34 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/02 22:56:38 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL2/SDL.h"
#include "wx_frame_buffer.h"
#include "wx_types.h"
#include "we_editor.h"

static t_bool	zz_on_error(t_editor *e, t_u8 i)
{
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
	wx_buffer_set(e, sizeof(*e), 0);
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
	e->quit = wx_false;
	return (wx_true);
}
