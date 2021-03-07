/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_darray.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:50:23 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/07 15:59:36 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WC_DARRAY_H
# define WC_DARRAY_H

# include "wx_types.h"

/*
** 2021-03-07 note: all internal sizes in bytes
*/

struct	s_darray
{
	void	*buffer;
	t_u64	buffer_size;
	t_u64	element_size;
	t_u64	size;
};
typedef struct s_darray	t_darray;

t_bool	wc_darray_new(t_darray *d, t_u64 reserved_elements, t_u64 element_size);
t_bool	wc_darray_new_file(t_darray *d, char const *filename,
	t_u64 element_size);
void	wc_darray_del(t_darray *d);
t_bool	wc_darray_add_back(t_darray *d, void const *x);
t_bool	wc_darray_add_back_be(t_darray *d, void const *b, void const *e);

#endif
