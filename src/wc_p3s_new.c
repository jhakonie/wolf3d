/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_p3s_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 11:44:40 by name          #+#    #+#             */
/*   Updated: 2021/04/12 22:01:45 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wc_parse.h"

t_bool	wc_p3s_new(t_p3s *c, t_u64 buffer_size)
{
	wx_buffer_set(c, sizeof(*c), 0);
	if (buffer_size)
	{
		c->buffer = (t_p3 *)malloc(buffer_size * sizeof(t_p3));
		if (!c->buffer)
		{
			return (wx_false);
		}
		c->buffer_size = buffer_size;
	}
	c->size = 0;
	return (wx_true);
}
