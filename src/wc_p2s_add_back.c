/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_p2s_add_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 12:00:51 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/04/12 22:01:45 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wx_parse.h"

t_bool	wc_p2s_add_back(t_p2s *c, t_p2 const *v)
{
	t_p2	*new_buffer;
	t_u64	new_buffer_size;
	t_u64	new_size;

	new_size = c->size + 1;
	if (new_size > c->buffer_size)
	{
		new_buffer_size = 2 * c->buffer_size;
		new_buffer = (t_p2 *)malloc(new_buffer_size * sizeof(t_p2));
		if (!new_buffer)
		{
			return (wx_false);
		}
		wx_buffer_copy(new_buffer, c->buffer, c->buffer_size
			* sizeof(t_p2));
		free(c->buffer);
		c->buffer = new_buffer;
		c->buffer_size = new_buffer_size;
	}
	c->buffer[c->size] = *v;
	++c->size;
	return (wx_true);
}
