/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:30:21 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/05 12:48:53 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"

/*
** 2021-06-18 todo: remove?
*/
void	wc_draw_clear(t_draw_context *dc)
{
	wx_buffer_set(dc->frame_buffer->data, dc->frame_buffer->data_size, 0);
	wx_buffer_set(dc->depth_buffer->data, dc->depth_buffer->data_size, 0);
}
