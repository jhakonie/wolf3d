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

void	wc_client_del(t_client *c)
{
	free(c->pipeline_buffers.visible_indices);
	free(c->pipeline_buffers.view_positions);
	free(c->pipeline_buffers.screen_positions);
	wc_mesh_del(&c->unit_cube);
	wc_remote_server_del(&c->remote_server);
	wc_depth_buffer_del(&c->depth_buffer);
	wx_frame_buffer_del(&c->frame_buffer);
	SDL_DestroyTexture(c->texture);
	SDL_DestroyRenderer(c->renderer);
	SDL_DestroyWindow(c->window);
	SDL_Quit();
}
