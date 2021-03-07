/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_darray_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:56:39 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/07 12:58:09 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wc_darray.h"

/*
** 2021-03-07 note: setting members to 0 so easy to recognize destroyed object.
** it's unnecessary but may come in handy
*/

void	wc_darray_del(t_darray *d)
{
	free(d->buffer);
	d->buffer = WX_NULL;
	d->buffer_size = 0;
	d->element_size = 0;
	d->size = 0;
}
