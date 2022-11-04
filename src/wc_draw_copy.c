/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw_copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: name <name@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:41:07 by name          #+#    #+#             */
/*   Updated: 2021/03/24 14:46:56 by name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_client.h"
#include "wc_draw.h"

/*
** 2021-02-17 todo: should copy in blocks if texture_pitch happens to be
** something unexpected
*/

void	wc_draw_copy(t_client *c, t_frame_buffer const *fb)
{
	t_u8	*texture_data;
	t_s32	texture_pitch;

	if (SDL_LockTexture(c->texture, WX_NULL, (void **)&texture_data,
			&texture_pitch) < 0)
	{
		c->run = wx_false;
	}
	wx_buffer_copy(texture_data, fb->data, fb->data_size);
	SDL_UnlockTexture(c->texture);
	if (SDL_RenderCopy(c->renderer, c->texture, WX_NULL, WX_NULL) < 0)
	{
		c->run = wx_false;
	}
	SDL_RenderPresent(c->renderer);
}
