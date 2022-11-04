/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_c8s_new_from_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 22:33:11 by name          #+#    #+#             */
/*   Updated: 2021/04/12 22:31:11 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fcntl.h"
#include "stdlib.h"
#include "unistd.h"

#include "wx_parse.h"

static t_bool	zz_c8s_add_back_be(t_c8s *c, void const *b, void const *e)
{
	void	*new_buffer;
	t_u64	new_size;

	new_size = c->size + (e - b);
	if (c->buffer_size < new_size)
	{
		if (new_size < (2 * c->buffer_size))
		{
			new_size = 2 * c->buffer_size;
		}
		new_buffer = (void *)malloc(new_size);
		if (!new_buffer)
		{
			return (wx_false);
		}
		wx_buffer_copy(new_buffer, c->buffer, c->buffer_size);
		free(c->buffer);
		c->buffer = new_buffer;
		c->buffer_size = new_size;
	}
	wx_buffer_copy(c->buffer + c->size, b, e - b);
	c->size += e - b;
	return (wx_true);
}

static t_bool	zz_c8s_new(t_c8s *c, t_u64 buffer_size)
{
	wx_buffer_set(c, sizeof(*c), 0);
	if (buffer_size)
	{
		c->buffer = (t_c8 *)malloc(buffer_size);
		if (!c->buffer)
		{
			return (wx_false);
		}
		c->buffer_size = buffer_size;
	}
	c->size = 0;
	return (wx_true);
}

static t_bool	zz_on_error(t_c8s *c, int fd)
{
	close(fd);
	wx_c8s_del(c);
	return (wx_false);
}

t_bool	wx_c8s_new_from_file(t_c8s *c, t_u64 buffer_size, char const *filename)
{
	char		buffer[4096];
	int			fd;
	ssize_t		read_size;

	if (!zz_c8s_new(c, buffer_size))
		return (wx_false);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (zz_on_error(c, fd));
	while (wx_true)
	{
		read_size = read(fd, buffer, sizeof(buffer));
		if (read_size <= 0)
		{
			break ;
		}
		if (!zz_c8s_add_back_be(c, buffer, buffer + read_size))
			return (zz_on_error(c, fd));
	}
	if (read_size == -1)
		return (zz_on_error(c, fd));
	close(fd);
	return (wx_true);
}
