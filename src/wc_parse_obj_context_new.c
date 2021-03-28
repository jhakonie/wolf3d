/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse_obj_context_new.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 08:48:02 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/28 08:48:02 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_parse.h"

static t_bool	zz_on_error(t_parse_obj_context *poc, t_u8 i)
{
	if (i > 2)
	{
		wc_p3s_del(&poc->positions);
	}
	if (i > 1)
	{
		wc_n3s_del(&poc->normals);
	}
	if (i > 0)
	{
		wc_obj_vertices_del(&poc->vertices);
	}
	return (wx_false);
}

t_bool	wc_parse_obj_context_new(t_parse_obj_context *poc)
{
	if (!wc_obj_vertices_new(&poc->vertices, 1024))
		return (zz_on_error(poc, 0));
	if (!wc_n3s_new(&poc->normals, 1024))
		return (zz_on_error(poc, 1));
	if (!wc_p3s_new(&poc->positions, 1024))
		return (zz_on_error(poc, 2));
	if (!wc_p2s_new(&poc->uvs, 1024))
		return (zz_on_error(poc, 3));
	return (wx_true);
}
