/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:00:01 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/24 20:54:38 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_frame_buffer.h"
#include "wx_types.h"
#include "we_editor.h"

int				main(void)
{
	t_editor	e;

	e.quit = wx_false;
	if (!(we_editor_new(&e, WE_WIN_W, WE_WIN_H)))
		return (-1);
	if (!(we_editor_run(&e)))
	{
		we_editor_del(&e);
		return (-1);
	}
	we_editor_del(&e);
	return (0);
}
