/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_packet_read_f32.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: name <name@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:29:29 by name          #+#    #+#             */
/*   Updated: 2021/02/16 22:02:31 by name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_net.h"

void	wx_packet_read_f32(t_packet *p, t_f32 *x)
{
	wx_buffer_copy(x, p->buffer + p->read_i, sizeof(*x));
	p->read_i += sizeof(*x);
}
