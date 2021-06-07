/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_save_map_to_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:53:52 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/07 16:30:36 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static t_bool	zz_create_directory(t_c8 *level)
{
	t_path	p;

	if (!we_path_create(&p, "data/maps/", level, ""))
		return (wx_false);
	if (mkdir(p.buffer, 0777) < 0)
	{
		write(1, "mkdir failed\n", 14);
		we_path_del(&p);
		return (wx_false);
	}
	we_path_del(&p);
	return (wx_true);
}

static t_bool	zz_remove_directory(t_c8 *level)
{
	t_path	p;

	if (!we_path_create(&p, "data/maps/", level, ""))
		return (wx_false);
	if (rmdir(p.buffer) < 0)
	{
		write(1, "rmdir failed\n", 14);
		we_path_del(&p);
		return (wx_false);
	}
	we_path_del(&p);
	return (wx_true);
}

static t_s32	zz_open(t_c8 *file_path, t_c8 *level_name)
{
	t_s32	fd;

	fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		if (!zz_create_directory(level_name))
			return (-1);
		fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
		{
			zz_remove_directory(level_name);
			return (-1);
		}
	}
	return (fd);
}

void	we_save_map_to_file(t_editor *e)
{
	t_u32	i;
	t_s32	fd;
	t_u8	block;

	i = 0;
	fd = zz_open(e->map.level.paths[we_map].buffer, e->map.level.name);
	if (fd < 0)
		return ;
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
