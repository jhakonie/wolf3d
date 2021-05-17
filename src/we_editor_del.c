/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_editor_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:49:37 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/17 16:05:25 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "we_editor.h"

void	we_editor_del(t_editor *e)
{
	free(e->frame_buffer.data);
	SDL_DestroyTexture(e->texture);
	SDL_DestroyRenderer(e->renderer);
	SDL_DestroyWindow(e->window);
	SDL_Quit();
}
