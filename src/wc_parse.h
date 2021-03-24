/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 09:56:03 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 14:49:20 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WC_PARSE_H
# define WC_PARSE_H

# include "wx_types.h"

typedef struct s_mesh			t_mesh;

struct	s_parse_context
{
	char const	*p;
	char const	*e;
};
typedef struct s_parse_context	t_parse_context;

t_bool	wc_parse_comment(t_parse_context *pc);
t_bool	wc_parse_face(t_parse_context *pc, t_mesh *m);
t_bool	wc_parse_f32(t_parse_context *pc, t_f32 *n);
t_bool	wc_parse_keyword(t_parse_context *pc, char const *k);
t_bool	wc_parse_material_filename(t_parse_context *pc);
t_bool	wc_parse_material_name(t_parse_context *pc);
t_bool	wc_parse_normal(t_parse_context *pc, t_mesh *m);
t_bool	wc_parse_object_name(t_parse_context *pc);
t_bool	wc_parse_position(t_parse_context *pc, t_mesh *m);
t_bool	wc_parse_smoothing(t_parse_context *pc);
t_bool	wc_parse_u16(t_parse_context *pc, t_u16 *n);
t_bool	wc_parse_u32(t_parse_context *pc, t_u32 *n);
t_bool	wc_parse_uv(t_parse_context *pc, t_mesh *m);
t_bool	wc_parse_whitespace(t_parse_context *pc);

#endif
