/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_depth_buffer_new.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:19:44 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/04/12 16:19:44 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wc_draw.h"

t_bool	wc_depth_buffer_new(t_depth_buffer *db, t_u32 width, t_u32 height)
{
	db->data_size = width * height * sizeof(t_f32);
	db->data = (t_f32 *)malloc(db->data_size);
	if (!db->data)
	{
		return (wx_false);
	}
	wx_buffer_set(db->data, db->data_size, 0);
	db->width = width;
	db->height = height;
	return (wx_true);
}
