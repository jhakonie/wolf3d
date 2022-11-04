/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: name <name@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:34:00 by name          #+#    #+#             */
/*   Updated: 2021/01/27 11:47:19 by name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_client.h"
#include "wx_types.h"

int	main(int as_size, char **as)
{
	t_client	c;
	char const	*map_name;

	map_name = as[1];
	if (as_size < 2)
	{
		map_name = "default";
	}
	if (!wc_client_new(&c, 800, 450, map_name))
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
