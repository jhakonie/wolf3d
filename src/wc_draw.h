/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 23:38:47 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/29 19:13:05 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WC_DRAW_H
# define WC_DRAW_H

# include "wx_frame_buffer.h"
# include "wx_math.h"

typedef struct s_client				t_client;
typedef struct s_pipeline_vertex	t_pipeline_vertex;

struct	s_camera
{
	t_q4		orientation;
	t_p3		position;
	t_f32		hfov_rad;
	t_f32		aspect_ratio;
	t_f32		near;
	t_f32		far;
};
typedef struct s_camera				t_camera;

struct	s_clip_context
{
	t_plane_line	cs;
	t_u16			out_indices[4];
	t_u64			out_indices_size;
	t_u16			i0;
	t_u16			i1;
	t_f32			t;
};
typedef struct s_clip_context		t_clip_context;

struct	s_face
{
	t_u16	indices[3];
};
typedef struct s_face				t_face;

/*
** 2021-03-26 note: sizes are in number of t_u16-sized elements. not in bytes
*/
struct	s_u16s
{
	t_u16	*buffer;
	t_u64	buffer_size;
	t_u64	size;
};
typedef struct s_u16s				t_u16s;

t_bool	wc_u16s_new(t_u16s *c, t_u64 buffer_size);
void	wc_u16s_del(t_u16s *c);
t_bool	wc_u16s_add_back(t_u16s *c, t_u16 const *v);

struct	s_vertex
{
	t_p3	position;
	t_n3	normal;
	t_p2	uv;
};
typedef struct s_vertex				t_vertex;

/*
** 2021-03-26 note: sizes are in number of vertex-sized elements. not in bytes
*/
struct	s_vertices
{
	t_vertex	*buffer;
	t_u64		buffer_size;
	t_u64		size;
};
typedef struct s_vertices			t_vertices;

t_bool	wc_vertices_new(t_vertices *c, t_u64 buffer_size);
void	wc_vertices_del(t_vertices *c);
t_bool	wc_vertices_add_back(t_vertices *c, t_vertex const *v);

/*
** 2021-03-26 note: a mesh contains a single index buffer used to index into the
** vertex buffer. meaning that some file formats, such as obj for example where
** there is an index buffer per-vertex-attribute, need be flattened and new
** vertices inserted for every unique combination of vertex attributes.
**
** every three indices forms a triangular face of the mesh.
**
** for now an array-of-struct approach was chosen and investigating a
** struct-of-arrays approach is left for another time
*/
struct	s_mesh
{
	t_aabb		aabb;
	t_u16s		indices;
	t_vertices	vertices;
};
typedef struct s_mesh				t_mesh;

t_bool	wc_mesh_new(t_mesh *m, char const *filename);
void	wc_mesh_del(t_mesh *m);

struct	s_pipeline_buffers
{
	t_p3	*screen_positions;
	t_u64	screen_positions_size;
	t_p3	*view_positions;
	t_u64	view_positions_size;
	t_u16	*visible_indices;
	t_u64	visible_indices_size;
};
typedef struct s_pipeline_buffers	t_pipeline_buffers;

struct	s_draw_context
{
	t_pipeline_buffers	*buffers;
	t_m44				clip_from_view;
	t_frame_buffer		*frame_buffer;
	t_frustum			frustum;
	t_m44				view_from_object;
};
typedef struct s_draw_context		t_draw_context;

/* struct	s_pipeline_vertex */
/* { */
/*	t_p3	view_position; */
/* }; */

struct	s_rectangle
{
	t_p2	p0;
	t_p2	p1;
};
typedef struct s_rectangle			t_rectangle;

void	wc_draw(t_client *c);
void	wc_draw_add_visible(t_draw_context *dc, t_clip_context const *cc);
void	wc_draw_clear(t_frame_buffer *fb);
void	wc_draw_clip(t_draw_context *dc, t_face const *f, t_plane const *p);
void	wc_draw_copy(t_client *c, t_frame_buffer const *fb);
void	wc_draw_mesh(t_draw_context *dc, t_mesh const *m);
void	wc_draw_pixel(t_frame_buffer *fb, t_f32 x, t_f32 y, t_u32 abgr);
void	wc_draw_rectangle_outline(t_frame_buffer *fb, t_p3 p, t_f32 width,
			t_u32 abgr);
void	wc_draw_rectangle_solid(t_frame_buffer *fb, t_p3 p, t_f32 width,
			t_u32 abgr);

#endif
