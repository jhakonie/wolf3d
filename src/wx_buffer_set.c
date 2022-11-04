/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_buffer_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: name <name@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 10:58:54 by name          #+#    #+#             */
/*   Updated: 2021/01/27 10:59:57 by name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_types.h"

void	wx_buffer_set(void *xs, t_u64 xs_size, t_u8 x)
{
	t_u64	i;

	i = 0;
	while (i < xs_size)
	{
		((t_u8 *)xs)[i] = x;
		++i;
	}
}
