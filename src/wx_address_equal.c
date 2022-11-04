/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_address_equal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: name <name@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:34:27 by name          #+#    #+#             */
/*   Updated: 2021/02/17 10:37:14 by name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_net.h"

t_bool	wx_address_equal(struct sockaddr const *a0, socklen_t a0_size,
	struct sockaddr const *a1, socklen_t a1_size)
{
	t_u64	i;

	if (a0_size != a1_size)
	{
		return (wx_false);
	}
	if (a0->sa_family != a1->sa_family)
	{
		return (wx_false);
	}
	i = 0;
	while (i < a0_size)
	{
		if (a0->sa_data[i] != a1->sa_data[i])
		{
			return (wx_false);
		}
		++i;
	}
	return (wx_true);
}
