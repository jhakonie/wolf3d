/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_obj_vertices_del.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 11:26:33 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/27 11:26:33 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wc_parse.h"

void	wc_obj_vertices_del(t_obj_vertices *c)
{
	free(c->buffer);
}
