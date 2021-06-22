/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_texture_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:59:14 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/05/01 15:59:14 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wc_draw.h"

void	wc_texture_del(t_texture *t)
{
	free(t->buffer);
	wx_buffer_set(t, sizeof(*t), 0);
}
