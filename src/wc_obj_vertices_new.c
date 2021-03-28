/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_obj_vertices_new.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 11:27:01 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/27 11:27:01 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wc_parse.h"

t_bool	wc_obj_vertices_new(t_obj_vertices *c, t_u64 buffer_size)
{
	wx_buffer_set(c, sizeof(*c), 0);
	if (buffer_size)
	{
		c->buffer = (t_obj_vertex *)malloc(buffer_size * sizeof(t_obj_vertex));
		if (!c->buffer)
		{
			return (wx_false);
		}
		c->buffer_size = buffer_size;
	}
	c->size = 0;
	return (wx_true);
}
