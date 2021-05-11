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
	t_f32	angle_rad;
	t_v3	axis;

	axis = (t_v3){0.0f, 1.0f, 0.0f};
	angle_rad = wx_to_radians(-135.0f);
	c->camera.orientation = wx_q4_new_v3_f32(&axis, angle_rad);
	c->camera.position = (t_p3){4.0f, 0.0f, 4.0f};
	c->camera.hfov_rad = wx_to_radians(90.0f);
	c->camera.aspect_ratio = width / height;
	c->camera.near = 0.1f;
	c->camera.far = 1000.0f;
}

/*
** 2021-05-01 todo: this is not working out too well. firstly it is confusing
** and secondly does not scale very well as new things keep getting added to the
** client struct. so sort it out
*/
static t_bool	zz_on_error(t_client *c, t_u8 i)
{
	if (i > 9)
		wc_pipeline_buffers_del(&c->pipeline_buffers);
	if (i > 8)
		wc_texture_del(&c->test_texture);
	if (i > 7)
		wc_mesh_del(&c->test_mesh);
	if (i > 6)
		wc_remote_server_del(&c->remote_server);
	if (i > 5)
		wc_depth_buffer_del(&c->depth_buffer);
	if (i > 4)
		wx_frame_buffer_del(&c->frame_buffer);
	if (i > 3)
		SDL_DestroyTexture(c->texture);
	if (i > 2)
		SDL_DestroyRenderer(c->renderer);
	if (i > 1)
		SDL_DestroyWindow(c->window);
	if (i > 0)
		SDL_Quit();
	return (wx_false);
}

static t_bool	zz_sdl(t_client *c, t_u32 window_width, t_u32 window_height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (zz_on_error(c, 0));
	c->window = SDL_CreateWindow("wolf3d_client", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, window_width, window_height, 0);
	if (!c->window)
		return (zz_on_error(c, 1));
	c->renderer = SDL_CreateRenderer(c->window, -1, 0);
	if (!c->renderer)
		return (zz_on_error(c, 2));
	c->texture = SDL_CreateTexture(c->renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
	if (!c->texture)
		return (zz_on_error(c, 3));
	return (wx_true);
}

t_bool	wc_client_new(t_client *c, t_u32 window_width, t_u32 window_height)
{
	wx_buffer_set(c, sizeof(*c), 0);
	if (!zz_sdl(c, window_width, window_height))
		return (wx_false);
	if (!wx_frame_buffer_new(&c->frame_buffer, window_width, window_height))
		return (zz_on_error(c, 4));
	if (!wc_depth_buffer_new(&c->depth_buffer, window_width, window_height))
		return (zz_on_error(c, 5));
	if (!wc_remote_server_new(&c->remote_server, "localhost",
			WX_SERVER_DEFAULT_SOCKET))
		return (zz_on_error(c, 6));
	if (!wc_mesh_new(&c->test_mesh, "data/unit_cube.obj"))
		return (zz_on_error(c, 7));
	if (!wc_texture_new_from_file(&c->test_texture, "data/unit_cube.xpm"))
		return (zz_on_error(c, 8));
	if (!wc_pipeline_buffers_new(&c->pipeline_buffers))
		return (zz_on_error(c, 9));
	zz_camera(c, window_width, window_height);
	c->sim_time_s = wx_time_s();
	c->sim_time_step_s = 1.0 / 30.0;
	c->run = wx_true;
	return (wx_true);
}
