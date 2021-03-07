/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_darray_add_back_be.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:58:32 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/07 19:20:22 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wc_darray.h"

t_bool	wc_darray_add_back_be(t_darray *d, void const *b, void const *e)
{
	void	*buffer;
	t_u64	new_size;

	new_size = d->size + (e - b);
	if (d->buffer_size < new_size)
	{
		if (new_size < (2 * d->buffer_size))
		{
			new_size = 2 * d->buffer_size;
		}
		buffer = (void *)malloc(new_size);
		if (!buffer)
		{
			return (wx_false);
		}
		wx_buffer_copy(buffer, d->buffer, d->buffer_size);
		free(d->buffer);
		d->buffer = buffer;
		d->buffer_size = new_size;
	}
	wx_buffer_copy(d->buffer + d->size, b, e - b);
	d->size += e - b;
	return (wx_true);
}
