/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_editor_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:14:34 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/09 22:17:51 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"
#include "wx_time.h"

static t_bool	zz_on_error(t_editor *e, t_u8 i)
{
	if (i > 5)
		we_level_del(&e->map.level);
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

static t_bool	zz_default_texture_paths(t_path *p)
{
	if (!wx_path_new3(&p[we_wall_north],
			"data/maps/", "default", "/north.xpm")
		|| !wx_path_new3(&p[we_wall_east],
			"data/maps/", "default", "/east.xpm")
		|| !wx_path_new3(&p[we_wall_south],
			"data/maps/", "default", "/south.xpm")
		|| !wx_path_new3(&p[we_wall_west],
			"data/maps/", "default", "/west.xpm")
		|| !wx_path_new3(&p[we_floor],
			"data/maps/", "default", "/floor.xpm")
		|| !wx_path_new3(&p[we_sky],
			"data/maps/", "default", "/sky.xpm")
		|| !wx_path_new3(&p[we_door],
			"data/maps/", "default", "/door.xpm"))
	{
		return (wx_false);
	}
	return (wx_true);
}

static t_bool	zz_set_default_textures(t_level *l)
{
	wx_buffer_set(l->paths, sizeof(*l->paths), 0);
	if (!wx_path_new3(&l->paths[we_map], "data/maps/", l->name, "/map.txt")
		|| !zz_default_texture_paths(l->paths))
	{
		return (we_paths_del(l->paths, WE_RESOURCES_COUNT));
	}
	wx_buffer_set(&l->texture_type, sizeof(t_level_texture), 0);
	if (!we_texture_type_new(&l->texture_type, l->paths))
	{
		we_paths_del(l->paths, WE_RESOURCES_COUNT);
		return (wx_false);
	}
	return (wx_true);
}

t_bool	we_editor_new(t_editor *e, t_u32 window_width, t_u32 window_height)
{
	if (!zz_sdl(e, window_width, window_height))
		return (wx_false);
	if (!wx_frame_buffer_new(&e->frame_buffer, window_width, window_height))
		return (zz_on_error(e, 4));
	wx_buffer_set(&e->tools, sizeof(e->tools), 0);
	if (!we_level_new(&e->map.level))
	{
		if (!zz_set_default_textures(&e->map.level))
			return (zz_on_error(e, 5));
	}
	we_init_map(&e->map, window_width, window_height);
	we_init_tiles(&e->map);
	we_init_toolbar(&e->tools, window_width, window_height);
	if (!we_toolbar_icons_new(e->tools.tool))
		return (zz_on_error(e, 6));
	we_init_player(&e->player, &e->map, e->frame_buffer.width);
	e->quit = wx_false;
	e->draw = wx_true;
	e->map.draw_3d = wx_false;
	e->time.sim_time_s = wx_time_s();
	e->time.sim_time_step_s = 1.0 / 30.0;
	return (wx_true);
}
