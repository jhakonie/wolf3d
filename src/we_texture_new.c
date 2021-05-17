/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_texture_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 18:22:27 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/14 19:25:44 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

t_bool	we_texture_new(char *filename, t_tex *t)
{
	t_xpm	xpm;

	if (!wx_parse_xpm(filename, &xpm))
		return (wx_false);
	if (xpm.height != xpm.width)
	{
		wx_xpm_del(&xpm);
		write(1, "Error: texture must be square shaped.\n", 39);
		return (wx_false);
	}
	t->height = xpm.height;
	t->width = xpm.width;
	t->size = xpm.width * xpm.height * sizeof(t_u32);
	wx_buffer_set(t->fractal, 2500, 0);
	t->texture = (t_u32 *)malloc(t->size);
	if (!t->texture)
	{
		wx_xpm_del(&xpm);
		return (wx_false);
	}
	wx_buffer_copy(t->texture, xpm.pixels, t->size);
	wx_xpm_del(&xpm);
	return (wx_true);
}
