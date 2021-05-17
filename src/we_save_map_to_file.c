/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_save_map_to_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:53:52 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/17 16:24:39 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	we_save_map_to_file(t_editor *e)
{
	t_u32	i;
	t_s32	fd;
	t_u8	block;

	i = 0;
	fd = open(e->map.file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		write(1, "open failed\n", 13);
	while (i < e->map.block_count)
	{
		if (e->map.tiles[i].id > 0)
			block = e->map.tiles[i].id + '0';
		else
			block = '.';
		write(fd, &block, 1);
		if ((int)e->map.tiles[i].block.x != WE_GRID_DIVIDE - 1)
			write(fd, " ", 1);
		else if ((int)e->map.tiles[i].block.x == WE_GRID_DIVIDE - 1)
			write(fd, "\n", 1);
		i++;
	}
	close(fd);
}
