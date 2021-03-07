/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_darray_add_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:50:13 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/07 15:51:35 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_darray.h"

t_bool	wc_darray_add_back(t_darray *d, void const *x)
{
	return (wc_darray_add_back_be(d, x, x + d->element_size));
}
