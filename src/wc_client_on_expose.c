/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_client_on_expose.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:33:22 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/01/27 11:37:21 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_client.h"

/*
** 2021-01-27 todo: should copy in blocks if texture_pitch happens to be
** something unexpected
*/

void	wc_client_on_expose(t_client *c)
{
	t_u8	*texture_data;
	t_s32	texture_pitch;

	if (SDL_LockTexture(c->texture, NULL, (void **)&texture_data,
		&texture_pitch) < 0)
	{
		c->run = wx_false;
	}
	wx_buffer_copy(texture_data, c->frame_buffer.data,
		c->frame_buffer.data_size);
	SDL_UnlockTexture(c->texture);
	if (SDL_RenderCopy(c->renderer, c->texture, NULL, NULL) < 0)
	{
		c->run = wx_false;
	}
	SDL_RenderPresent(c->renderer);
}
