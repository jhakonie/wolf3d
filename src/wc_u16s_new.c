/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_u16s_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 11:45:14 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/26 11:45:14 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wc_draw.h"

t_bool	wc_u16s_new(t_u16s *c, t_u64 buffer_size)
{
	wx_buffer_set(c, sizeof(*c), 0);
	if (buffer_size)
	{
		c->buffer = (t_u16 *)malloc(buffer_size * sizeof(t_u16));
		if (!c->buffer)
		{
			return (wx_false);
		}
		c->buffer_size = buffer_size;
	}
	c->size = 0;
	return (wx_true);
}
