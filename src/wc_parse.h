/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 09:56:03 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/04/12 22:37:53 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WC_PARSE_H
# define WC_PARSE_H

# include "wc_draw.h"

# include "wx_types.h"

typedef struct s_mesh				t_mesh;
typedef struct s_parse_context		t_parse_context;

/*
** 2021-04-26 note: sizes are in number of t_n3-sized elements. not in bytes
*/
struct	s_n3s
{
	t_n3	*buffer;
	t_u64	buffer_size;
	t_u64	size;
};
typedef struct s_n3s				t_n3s;

t_bool	wc_n3s_new(t_n3s *c, t_u64 buffer_size);
void	wc_n3s_del(t_n3s *c);
t_bool	wc_n3s_add_back(t_n3s *c, t_n3 const *v);

/*
** 2021-04-26 note: sizes are in number of t_p2-sized elements. not in bytes
*/
struct	s_p2s
{
	t_p2	*buffer;
	t_u64	buffer_size;
	t_u64	size;
};
typedef struct s_p2s				t_p2s;

t_bool	wc_p2s_new(t_p2s *c, t_u64 buffer_size);
void	wc_p2s_del(t_p2s *c);
t_bool	wc_p2s_add_back(t_p2s *c, t_p2 const *v);

/*
** 2021-04-26 note: sizes are in number of t_p3-sized elements. not in bytes
*/
struct	s_p3s
{
	t_p3	*buffer;
	t_u64	buffer_size;
	t_u64	size;
};
typedef struct s_p3s				t_p3s;

t_bool	wc_p3s_new(t_p3s *c, t_u64 buffer_size);
void	wc_p3s_del(t_p3s *c);
t_bool	wc_p3s_add_back(t_p3s *c, t_p3 const *v);

struct	s_obj_vertex
{
	t_u16	position;
	t_u16	normal;
	t_u16	uv;
	t_u16	out_index;
};
typedef struct s_obj_vertex			t_obj_vertex;

/*
** 2021-04-27 note: sizes are in number of t_obj_vertex-sized elements. not in
** bytes
*/
struct	s_obj_vertices
{
	t_obj_vertex	*buffer;
	t_u64			buffer_size;
	t_u64			size;
};
typedef struct s_obj_vertices		t_obj_vertices;

t_bool	wc_obj_vertices_new(t_obj_vertices *c, t_u64 buffer_size);
void	wc_obj_vertices_del(t_obj_vertices *c);
t_bool	wc_obj_vertices_add_back(t_obj_vertices *c, t_obj_vertex const *v);

struct	s_parse_obj_context
{
	t_obj_vertices	vertices;
	t_n3s			normals;
	t_p3s			positions;
	t_p2s			uvs;
};
typedef struct s_parse_obj_context	t_parse_obj_context;

t_bool	wc_parse_obj_context_new(t_parse_obj_context *poc);
void	wc_parse_obj_context_del(t_parse_obj_context *poc);

t_bool	wc_parse_obj(t_parse_context *pc, t_mesh *m);
t_bool	wc_parse_obj_comment(t_parse_context *pc);
t_bool	wc_parse_obj_face(t_parse_context *pc, t_obj_vertices *ofs);
t_bool	wc_parse_obj_material_filename(t_parse_context *pc);
t_bool	wc_parse_obj_material_name(t_parse_context *pc);
t_bool	wc_parse_obj_normal(t_parse_context *pc, t_n3s *n3s);
t_bool	wc_parse_obj_position(t_parse_context *pc, t_p3s *p3s);
t_bool	wc_parse_obj_uv(t_parse_context *pc, t_p2s *p2s);
t_bool	wc_parse_obj_object_name(t_parse_context *pc);
t_bool	wc_parse_obj_smoothing(t_parse_context *pc);
t_bool	wc_parse_u16(t_parse_context *pc, t_u16 *n);
t_bool	wc_parse_u32(t_parse_context *pc, t_u32 *n);

#endif
