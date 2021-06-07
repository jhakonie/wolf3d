/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_editor_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:49:37 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/07 15:03:36 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "we_editor.h"

void	we_editor_del(t_editor *e)
{
	free(e->frame_buffer.data);
	we_level_del(&e->map.level);
	SDL_DestroyTexture(e->texture);
	SDL_DestroyRenderer(e->renderer);
	SDL_DestroyWindow(e->window);
	SDL_Quit();
}
