/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_parse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 09:56:03 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/04/12 22:37:53 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WX_PARSE_H
# define WX_PARSE_H

# include "wx_types.h"

/*
** 2021-04-27 note: sizes are in number of t_c8-sized elements. not in bytes
*/
struct	s_c8s
{
	t_c8	*buffer;
	t_u64	buffer_size;
	t_u64	size;
};
typedef struct s_c8s				t_c8s;

t_bool	wx_c8s_new_from_file(t_c8s *c, t_u64 buffer_size, char const *filename);
void	wx_c8s_del(t_c8s *c);

struct	s_parse_context
{
	t_c8 const	*p;
	t_c8 const	*e;
};
typedef struct s_parse_context		t_parse_context;

t_bool	wx_parse_f32(t_parse_context *pc, t_f32 *n);
t_bool	wx_parse_keyword(t_parse_context *pc, char const *k);
t_bool	wx_parse_whitespace(t_parse_context *pc);

#endif
