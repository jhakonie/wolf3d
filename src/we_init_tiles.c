/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_init_tiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 22:38:50 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/14 19:24:23 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*
** todo: update zz buf to tiles on line 40 allowed numbers/chars
*/

static void	zz_add_char(t_map *m, char *buf, t_u32 i, t_u32 j)
{
	if (buf[i] == '.')
		m->level.tiles[j].id = 0;
	else
		m->level.tiles[j].id = buf[i] - '0';
}

static t_bool	zz_check_char(char *buf, t_u32 i)
{
	if (buf[i] == ' ' || buf[i] == '\n' || buf[i] == '.'
		|| buf[i] == '1' || buf[i] == '3' || buf[i] == '2')
		return (wx_true);
	return (wx_false);
}

/*
** Validates map characters and saves them to map_tiles.
*/
static t_bool	zz_buf_to_tiles(t_map *m, char *buf, t_u32 ret)
{
	t_u32		i;
	t_u32		j;

	i = 0;
	j = 0;
	while (i < ret)
	{	
		if (zz_check_char(buf, i))
		{
			if (buf[i] == ' ' || buf[i] == '\n')
			{
				if (buf[i] == '\n' && j % WE_GRID_DIVIDE != 0)
					break ;
				i++;
				if (i == ret)
					return (wx_true);
			}
			zz_add_char(m, buf, i, j);
			i++;
			j++;
		}
		else
			return (wx_false);
	}
	return (wx_false);
}

/*
** Opens a file, reads allowed numer of bytes + 1, to verify file length.
** Closes file. Updates map_tiles based on file.
**
** Assumes that read returns exactly as many bytes as requested.
*/
static t_bool	zz_load_file_to_tiles(t_map *m)
{
	t_s32		fd;
	t_s32		ret;
	char		buf[WE_MAP_BUFF_SIZE + 1];

	fd = open(m->level.paths[we_map].buffer, O_RDONLY, 0644);
	if (fd < 0)
	{
		write(1, "open failed\n", 13);
		return (wx_false);
	}
	ret = read(fd, buf, WE_MAP_BUFF_SIZE + 1);
	close(fd);
	if (ret < 0)
	{
		write(1, "read failed\n", 13);
		return (wx_false);
	}
	if (ret < WE_MAP_BUFF_SIZE || ret > WE_MAP_BUFF_SIZE)
	{
		write(1, "No pre-existing file or invalid map, save replaces it.\n", 56);
		return (wx_false);
	}
	return (zz_buf_to_tiles(m, buf, ret));
}

/*
** Initializes map_tiles array, loads a map from a file to tiles.
*/
void	we_init_tiles(t_map *m)
{
	we_tiles_set(m);
	if (!(zz_load_file_to_tiles(m)))
		we_tiles_set(m);
}
