/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_client_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:18:20 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/12 11:53:07 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wc_client.h"

static void	zz_map_textures_del(t_map_textures *mt)
{
	wc_texture_del(&mt->floor);
	wc_texture_del(&mt->door);
	wc_texture_del(&mt->walls[we_north]);
	wc_texture_del(&mt->walls[we_east]);
	wc_texture_del(&mt->walls[we_west]);
	wc_texture_del(&mt->walls[we_south]);
	wc_texture_del(&mt->skys[we_north]);
	wc_texture_del(&mt->skys[we_east]);
	wc_texture_del(&mt->skys[we_west]);
	wc_texture_del(&mt->skys[we_south]);
}

void	wc_client_del(t_client *c)
{
	free(c->pipeline_buffers.visible_indices);
	free(c->pipeline_buffers.view_positions);
	free(c->pipeline_buffers.uvs);
	free(c->pipeline_buffers.screen_positions);
	zz_map_textures_del(&c->map.textures);
	wc_map_mesh_del(&c->map_mesh);
	wc_mesh_del(&c->test_mesh);
	wc_texture_del(&c->test_texture);
	wc_remote_server_del(&c->remote_server);
	wc_depth_buffer_del(&c->depth_buffer);
	wx_frame_buffer_del(&c->frame_buffer);
	SDL_DestroyTexture(c->texture);
	SDL_DestroyRenderer(c->renderer);
	SDL_DestroyWindow(c->window);
	SDL_Quit();
}
