/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_depth_buffer_get.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:17:24 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/04/12 18:17:24 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"

t_f32	wc_depth_buffer_get(t_depth_buffer *db, t_f32 x, t_f32 y)
{
	t_u64	i;

	i = (t_u32)y * db->width + (t_u32)x;
	return (db->data[i]);
}
