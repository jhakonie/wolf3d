/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:00:01 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/24 15:28:17 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_frame_buffer.h"
#include "wx_types.h"
#include "we_editor.h"

static void	zz_arguments_check(t_editor *e, int ac, char **av)
{
	if (ac == 1)
		e->map.file = WX_NULL;
	else if (ac == 2)
		e->map.file = av[1];
	else
	{
		write(1, "wrong args\n", 11);
		exit(0);
	}
}

int	main(int ac, char **av)
{
	t_editor	e;

	wx_buffer_set(&e, sizeof(e), 0);
	zz_arguments_check(&e, ac, av);
	if (!(we_editor_new(&e, WE_WIN_W, WE_WIN_H)))
		return (-1);
	if (!(we_editor_run(&e)))
	{
		we_editor_del(&e);
		return (-1);
	}
	we_editor_del(&e);
	return (0);
}
