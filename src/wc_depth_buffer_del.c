/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_depth_buffer_del.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:22:30 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/04/12 16:22:30 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wc_draw.h"

void	wc_depth_buffer_del(t_depth_buffer *db)
{
	free(db->data);
	wx_buffer_set(db, sizeof(*db), 0);
}
