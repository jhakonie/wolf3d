/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_darray_new_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:54:12 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/07 12:55:19 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fcntl.h"
#include "unistd.h"

#include "wc_darray.h"

static t_bool	zz_on_error(t_darray *x, int fd)
{
	close(fd);
	wc_darray_del(x);
	return (wx_false);
}

t_bool			wc_darray_new_file(t_darray *d, char const *filename,
				size_t element_size)
{
	char		buffer[4096];
	int			fd;
	ssize_t		read_size;

	if (!wc_darray_new(d, 1, element_size))
		return (wx_false);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (zz_on_error(d, fd));
	while ((read_size = read(fd, buffer, sizeof(buffer))) > 0)
	{
		if (!wc_darray_add_back_be(d, buffer, buffer + read_size))
			return (zz_on_error(d, fd));
	}
	if (read_size == -1)
		return (zz_on_error(d, fd));
	close(fd);
	return (wx_true);
}
