/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ws_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: name <name@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:44:53 by name          #+#    #+#             */
/*   Updated: 2021/03/24 15:41:40 by name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ws_server.h"

int	main(void)
{
	t_server	s;

	if (!ws_server_new(&s))
	{
		return (-1);
	}
	if (!ws_server_run(&s))
	{
		ws_server_del(&s);
		return (-1);
	}
	ws_server_del(&s);
	return (0);
}
