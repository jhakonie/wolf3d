/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_p2s_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 11:43:28 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/04/12 22:01:45 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wx_parse.h"

t_bool	wc_p2s_new(t_p2s *c, t_u64 buffer_size)
{
	wx_buffer_set(c, sizeof(*c), 0);
	if (buffer_size)
	{
		c->buffer = (t_p2 *)malloc(buffer_size * sizeof(t_p2));
		if (!c->buffer)
		{
			return (wx_false);
		}
		c->buffer_size = buffer_size;
	}
	c->size = 0;
	return (wx_true);
}
