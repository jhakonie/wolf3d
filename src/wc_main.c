/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:34:00 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/01/27 11:47:19 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_client.h"
#include "wx_types.h"

int	main(void)
{
	t_client	c;

	if (!wc_client_new(&c, 800, 450))
	{
		return (-1);
	}
	if (!wc_client_run(&c))
	{
		wc_client_del(&c);
		return (-1);
	}
	wc_client_del(&c);
	return (0);
}
