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
