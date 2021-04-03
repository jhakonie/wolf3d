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
	angle_rad = wx_to_radians(180.0f);
	c->camera.orientation = wx_q4_new_v3_f32(&axis, angle_rad);
	c->camera.position = (t_p3){0.0f, 0.0f, 10.0f};
	c->camera.hfov_rad = wx_to_radians(90.0f);
	c->camera.aspect_ratio = width / height;
	c->camera.near = 0.1f;
	c->camera.far = 1000.0f;
}

static t_bool	zz_on_error(t_client *c, t_u8 i)
{
	if (i > 8)
		free(c->pipeline_buffers.visible_indices);
	if (i > 7)
		free(c->pipeline_buffers.view_positions);
	if (i > 6)
		free(c->pipeline_buffers.screen_positions);
	if (i > 5)
		wc_remote_server_del(&c->remote_server);
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

static t_bool	zz_pipeline(t_client *c)
{
	c->pipeline_buffers.screen_positions
		= (t_p3 *)malloc(WC_PIPELINE_VERTICES_SIZE * sizeof(t_p3));
	if (!c->pipeline_buffers.screen_positions)
		return (zz_on_error(c, 7));
	c->pipeline_buffers.screen_positions_size = 0;
	c->pipeline_buffers.view_positions
		= (t_p3 *)malloc(WC_PIPELINE_VERTICES_SIZE * sizeof(t_p3));
	if (!c->pipeline_buffers.view_positions)
		return (zz_on_error(c, 8));
	c->pipeline_buffers.view_positions_size = 0;
	c->pipeline_buffers.visible_indices
		= (t_u16 *)malloc(WC_PIPELINE_VERTICES_SIZE * sizeof(t_u16));
	if (!c->pipeline_buffers.visible_indices)
		return (zz_on_error(c, 9));
	c->pipeline_buffers.visible_indices_size = 0;
	return (wx_true);
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
	if (!wc_remote_server_new(&c->remote_server, "localhost",
			WX_SERVER_DEFAULT_SOCKET))
		return (zz_on_error(c, 5));
	if (!wc_mesh_new(&c->unit_cube, "data/unit_cube.obj"))
		return (zz_on_error(c, 6));
	if (!zz_pipeline(c))
		return (wx_false);
	zz_camera(c, window_width, window_height);
	c->sim_time_s = wx_time_s();
	c->sim_time_step_s = 1.0 / 30.0;
	c->run = wx_true;
	return (wx_true);
}
