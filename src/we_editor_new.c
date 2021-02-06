/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_editor_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:14:34 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/06 13:34:54 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void			zz_init_tool(t_tool *t, t_u32 win_width, t_u32 win_height)
{
	t->pre_selected = wx_false;
	t->selected = wx_false;
	t->button.start.x = win_width / 8;
	t->button.start.y = win_height / 8;
	t->button.end.x = t->button.start.x + WE_BTN_W;
	t->button.end.y = t->button.start.y + WE_BTN_H;
	we_u32_to_rgba(&t->button.color[0], 0xFFFFFF);
	we_u32_to_rgba(&t->button.color[1], 0x00FF00);
	we_u32_to_rgba(&t->button.color[2], 0xFF0000);
	we_u32_to_rgba(&t->button.color[3], 0x0000FF);
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
	e->draw = wx_true;
	wx_buffer_set(&e->tool, sizeof(e->tool), 0);
	zz_init_tool(&e->tool, window_width, window_width);
	return (wx_true);
}
