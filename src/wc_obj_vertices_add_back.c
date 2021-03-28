/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_obj_vertices_add_back.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 11:25:32 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/27 11:25:32 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wc_parse.h"

t_bool	wc_obj_vertices_add_back(t_obj_vertices *c, t_obj_vertex const *v)
{
	t_obj_vertex	*new_buffer;
	t_u64			new_buffer_size;
	t_u64			new_size;

	new_size = c->size + 1;
	if (new_size > c->buffer_size)
	{
		new_buffer_size = 2 * c->buffer_size;
		new_buffer = (t_obj_vertex *)malloc(new_buffer_size
				* sizeof(t_obj_vertex));
		if (!new_buffer)
		{
			return (wx_false);
		}
		wx_buffer_copy(new_buffer, c->buffer, c->buffer_size
			* sizeof(t_obj_vertex));
		free(c->buffer);
		c->buffer = new_buffer;
		c->buffer_size = new_buffer_size;
	}
	c->buffer[c->size] = *v;
	++c->size;
	return (wx_true);
}
