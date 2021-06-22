/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_vertices_del.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 11:13:17 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/27 11:13:17 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wc_draw.h"

void	wc_vertices_del(t_vertices *c)
{
	free(c->buffer);
	wx_buffer_set(c, sizeof(*c), 0);
}
