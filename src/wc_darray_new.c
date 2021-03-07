/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_darray_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:53:21 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/07 14:01:11 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wc_darray.h"

t_bool	wc_darray_new(t_darray *d, t_u64 reserved_elements, t_u64 element_size)
{
	wx_buffer_set(d, sizeof(*d), 0);
	if (reserved_elements)
	{
		d->buffer = (void *)malloc(reserved_elements * element_size);
		if (!d->buffer)
		{
			return (wx_false);
		}
		d->buffer_size = reserved_elements * element_size;
	}
	d->element_size = element_size;
	d->size = 0;
	return (wx_true);
}
