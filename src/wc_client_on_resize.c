/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_client_on_resize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:38:12 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/07 15:43:58 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_client.h"

void	wc_client_on_resize(t_client *c, t_s32 width, t_s32 height)
{
	SDL_DestroyTexture(c->texture);
	if (!(c->texture = SDL_CreateTexture(c->renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING, width, height)))
	{
		c->run = wx_false;
	}
	free(c->frame_buffer.data);
	c->frame_buffer.data = WX_NULL;
	c->frame_buffer.data_size = width * height * 4;
	if (!(c->frame_buffer.data = (t_u8 *)malloc(c->frame_buffer.data_size)))
	{
		c->run = wx_false;
	}
	wx_buffer_set(c->frame_buffer.data, c->frame_buffer.data_size, 0);
}
