/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_client_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:17:11 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 14:38:02 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_client.h"
#include "wx_net.h"
#include "wx_time.h"

static void	zz_camera(t_client *c, t_f32 width, t_f32 height)
{
	c->camera.orientation = (t_q4){0.0f, 0.0f, 0.0f, 1.0f};
	c->camera.position = (t_p3){0.0f, 0.0f, 0.0f};
	c->camera.hfov_rad = wx_to_radians(90.0f);
	c->camera.aspect_ratio = width / height;
	c->camera.near = 0.1f;
	c->camera.far = 1000.0f;
}

static t_bool	zz_map(t_client *c)
{
	t_map	m;

	if (!wc_map_new_from_file(&m, "data/maps/default/map.txt"))
	{
		return (wx_false);
	}
	if (!wc_map_mesh_new_from_map(&c->map_mesh, &m))
	{
		return (wx_false);
	}
	if (!wc_texture_new_from_file(&c->floor_texture,
			"data/maps/default/floor.xpm")
		|| !wc_texture_new_from_file(&c->north_texture,
			"data/maps/default/north.xpm")
		|| !wc_texture_new_from_file(&c->east_texture,
			"data/maps/default/east.xpm")
		|| !wc_texture_new_from_file(&c->west_texture,
			"data/maps/default/west.xpm")
		|| !wc_texture_new_from_file(&c->south_texture,
			"data/maps/default/south.xpm"))
	{
		return (wx_false);
	}
	return (wx_true);
}

static t_bool	zz_sdl(t_client *c, t_u32 window_width, t_u32 window_height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return (wx_false);
	}
	c->window = SDL_CreateWindow("wolf3d_client", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, window_width, window_height, 0);
	if (!c->window)
	{
		return (wx_false);
	}
	c->renderer = SDL_CreateRenderer(c->window, -1, 0);
	if (!c->renderer)
	{
		return (wx_false);
	}
	c->texture = SDL_CreateTexture(c->renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
	if (!c->texture)
	{
		return (wx_false);
	}
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_GetMouseState(&c->mouse_x, &c->mouse_y);
	return (wx_true);
}

t_bool	wc_client_new(t_client *c, t_u32 window_width, t_u32 window_height)
{
	wx_buffer_set(c, sizeof(*c), 0);
	if (!zz_sdl(c, window_width, window_height)
		|| !wx_frame_buffer_new(&c->frame_buffer, window_width, window_height)
		|| !wc_depth_buffer_new(&c->depth_buffer, window_width, window_height)
		|| !wc_remote_server_new(&c->remote_server, "localhost",
			WX_SERVER_DEFAULT_SOCKET)
		|| !wc_mesh_new_from_file(&c->test_mesh, "data/unit_cube.obj")
		|| !wc_texture_new_from_file(&c->test_texture, "data/unit_cube.xpm")
		|| !wc_pipeline_buffers_new(&c->pipeline_buffers)
		|| !zz_map(c))
	{
		wc_client_del(c);
		return (wx_false);
	}
	c->sim_time_s = wx_time_s();
	c->sim_time_step_s = 1.0 / 30.0;
	c->run = wx_true;
	c->player_orientation = (t_q4){0.0f, 0.0f, 0.0f, 1.0f};
	c->player_position = (t_p3){0.0f, 1.0f, 0.0f};
	zz_camera(c, window_width, window_height);
	return (wx_true);
}
