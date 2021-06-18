/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_texture_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 18:22:27 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/16 14:21:37 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

t_bool	we_texture_new(char *filename, t_texture *t)
{
	t_xpm	xpm;

	if (!wx_parse_xpm(filename, &xpm))
		return (wx_false);
	t->height = xpm.height;
	t->width = xpm.width;
	t->buffer_size = xpm.width * xpm.height * sizeof(t_u8) * 4;
	t->buffer = (t_u8 *)malloc(t->buffer_size);
	if (!t->buffer)
	{
		wx_xpm_del(&xpm);
		return (wx_false);
	}
	wx_buffer_copy(t->buffer, xpm.pixels, t->buffer_size);
	wx_xpm_del(&xpm);
	return (wx_true);
}
