/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_init_tiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 22:38:50 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/30 13:52:17 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static void	zz_add_char(t_map *m, char *buf, t_u32 i, t_u32 j)
{
	if (buf[i] == '.')
		m->tiles[j] = 0;
	else
		m->tiles[j] = buf[i] - '0';
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
				if (buf[i] == '\n' && j % WX_MAP_TILES_WIDTH != 0)
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
static t_bool	zz_load_file_to_tiles(t_level *l)
{
	t_s32		fd;
	t_s32		ret;
	char		buf[WX_MAP_READ_BUFF_SIZE + 1];

	fd = open(l->paths[we_map].buffer, O_RDONLY, 0644);
	if (fd < 0)
	{
		write(1, "open failed\n", 13);
		return (wx_false);
	}
	ret = read(fd, buf, WX_MAP_READ_BUFF_SIZE + 1);
	close(fd);
	if (ret < 0)
	{
		write(1, "read failed\n", 13);
		return (wx_false);
	}
	if (ret < WX_MAP_READ_BUFF_SIZE || ret > WX_MAP_READ_BUFF_SIZE)
	{
		write(1, "No pre-existing file or invalid map, save replaces it.\n", 56);
		return (wx_false);
	}
	return (zz_buf_to_tiles(&l->map, buf, ret));
}

/*
** Initializes map_tiles array, loads a map from a file to tiles.
*/
void	we_init_tiles(t_level *l)
{
	we_tiles_set(&l->map);
	if (!(zz_load_file_to_tiles(l)))
		we_tiles_set(&l->map);
	l->map.tile_width = WX_TILE_WIDTH;
	l->map.wall_height = WX_TILE_WIDTH;
	l->map.height = WX_MAP_TILES_WIDTH;
	l->map.width = WX_MAP_TILES_WIDTH;
}
