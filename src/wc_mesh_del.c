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
	wc_darray_del(&m->uvs);
	wc_darray_del(&m->positions);
	wc_darray_del(&m->normals);
	wc_darray_del(&m->faces);
}
