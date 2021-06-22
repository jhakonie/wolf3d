/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_mesh_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 03:24:01 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/20 06:48:50 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"

void	wc_mesh_del(t_mesh *m)
{
	wc_vertices_del(&m->vertices);
	wc_u16s_del(&m->indices);
	wx_buffer_set(m, sizeof(*m), 0);
}
