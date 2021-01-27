/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_client_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:18:20 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/01/27 11:46:38 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wc_client.h"

void	wc_client_del(t_client *c)
{
	free(c->frame_buffer.data);
	SDL_DestroyTexture(c->texture);
	SDL_DestroyRenderer(c->renderer);
	SDL_DestroyWindow(c->window);
	SDL_Quit();
}
