/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_frame_buffer_del.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:06:37 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/01/27 11:09:14 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wx_frame_buffer.h"

void	wx_frame_buffer_del(t_frame_buffer *fb)
{
	free(fb->data);
	wx_buffer_set(fb, sizeof(*fb), 0);
}
