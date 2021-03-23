/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_init_chart.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 22:38:50 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/08 19:36:59 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*
** todo: update zz buf to chart line 40 allowed numbers/chars
*/

static void		zz_add_char(t_map *m, char *buf, t_u32 i, t_u32 j)
{
	if (buf[i] == '.')
		m->chart[j].id = 0;
	else
		m->chart[j].id = buf[i] - '0';
}

static t_bool	zz_buf_to_chart(t_map *m, char *buf, t_u32 ret)
{
	t_u32		i;
	t_u32		j;

	i = 0;
	j = 0;
	while (i < ret)
	{
		if (buf[i] == ' ' || buf[i] == '\n' || buf[i] == '.' || buf[i] == '1'
			|| buf[i] == '3' || buf[i] == '2')
		{
			if (buf[i] == ' ' || buf[i] == '\n')
			{
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
	return (wx_true);
}

/*
** todo: add size to file name if already exists and is wrong size,
** add path to folder
*/

static t_bool	zz_save_file_to_chart(t_map *m)
{
	t_s32		fd;
	t_s32		ret;
	char		buf[WE_GRID_DIVIDE * WE_GRID_DIVIDE * 2];

	fd = open(m->file, O_RDONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		write(1, "open failed\n", 13);
		return (wx_false);
	}
	ret = read(fd, buf, WE_GRID_DIVIDE * WE_GRID_DIVIDE * 2);
	if (ret < 0)
	{
		write(1, "read failed\n", 13);
		return (wx_false);
	}
	if (ret != WE_GRID_DIVIDE * WE_GRID_DIVIDE * 2 && ret > 0)
	{
		write(1, "wrong map size or no existing file\n", 36);
		return (wx_false);
	}
	close(fd);
	return (zz_buf_to_chart(m, buf, ret));
}

static void		zz_set_empty_chart(t_map *m)
{
	t_u32		i;
	t_u32		x;
	t_u32		y;

	i = 0;
	y = 0;
	while (y < WE_GRID_DIVIDE)
	{
		x = 0;
		while (x < WE_GRID_DIVIDE)
		{
			m->chart[i].id = WE_ID_INIT;
			m->chart[i].block.x = x;
			m->chart[i].block.y = y;
			i++;
			x++;
		}
		y++;
	}
}

void			we_init_chart(t_map *m)
{
	zz_set_empty_chart(m);
	if (m->file)
	{
		if (!(zz_save_file_to_chart(m)))
			zz_set_empty_chart(m);
	}
}
