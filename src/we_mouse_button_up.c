/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_mouse_button_up.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 23:54:33 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/04 00:46:51 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_mouse_button_up(t_bool *ptr_hold, int event)
{
	if (event == SDL_BUTTON_LEFT)
		*ptr_hold = wx_false;
}
