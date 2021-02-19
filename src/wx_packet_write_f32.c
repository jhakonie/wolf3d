/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_packet_write_f32.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:32:30 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/16 16:49:01 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_net.h"

void	wx_packet_write_f32(t_packet *p, t_f32 x)
{
	wx_buffer_copy(p->buffer + p->size, &x, sizeof(x));
	p->size += sizeof(x);
}
