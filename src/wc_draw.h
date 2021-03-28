/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 23:38:47 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 14:46:35 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WC_DRAW_H
# define WC_DRAW_H

# include "wx_frame_buffer.h"
# include "wx_math.h"

typedef struct s_client			t_client;

struct	s_camera
{
	t_q4	orientation;
	t_p3	position;
	t_f32	hfov_rad;
	t_f32	aspect_ratio;
	t_f32	near;
	t_f32	far;
};
typedef struct s_camera			t_camera;

/*
** 2021-04-26 note: sizes are in number of t_u16-sized elements. not in bytes
*/
struct	s_u16s
{
	t_u16	*buffer;
	t_u64	buffer_size;
	t_u64	size;
};
typedef struct s_u16s			t_u16s;

t_bool	wc_u16s_new(t_u16s *c, t_u64 buffer_size);
void	wc_u16s_del(t_u16s *c);
t_bool	wc_u16s_add_back(t_u16s *c, t_u16 const *v);

struct	s_vertex
{
	t_p3	position;
	t_n3	normal;
	t_p2	uv;
};
typedef struct s_vertex			t_vertex;

/*
** 2021-04-26 note: sizes are in number of vertex-sized elements. not in bytes
*/
struct	s_vertices
{
	t_vertex	*buffer;
	t_u64		buffer_size;
	t_u64		size;
};
typedef struct s_vertices		t_vertices;
t_bool	wc_vertices_new(t_vertices *c, t_u64 buffer_size);
void	wc_vertices_del(t_vertices *c);
t_bool	wc_vertices_add_back(t_vertices *c, t_vertex const *v);

/*
** 2021-04-26 note: a mesh contains a single index buffer used to index into the
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
typedef struct s_mesh			t_mesh;

t_bool	wc_mesh_new(t_mesh *m, char const *filename);
void	wc_mesh_del(t_mesh *m);

struct	s_draw_context
{
	t_m44	clip_from_view;
	t_m44	ndc_from_clip;
	t_q4	object_orientation;
	t_p3	object_position;
	t_m44	view_from_world;
	t_m44	window_from_ndc;
	t_m44	world_from_object;
};
typedef struct s_draw_context	t_draw_context;

struct	s_rectangle
{
	t_p2	p0;
	t_p2	p1;
};
typedef struct s_rectangle		t_rectangle;

void	wc_draw(t_client *c);
void	wc_draw_clear(t_frame_buffer *fb);
void	wc_draw_copy(t_client *c, t_frame_buffer const *fb);
void	wc_draw_pixel(t_frame_buffer *fb, t_f32 x, t_f32 y, t_u32 abgr);
void	wc_draw_rectangle_outline(t_frame_buffer *fb, t_p3 p, t_f32 width,
			t_u32 abgr);
void	wc_draw_rectangle_solid(t_frame_buffer *fb, t_p3 p, t_f32 width,
			t_u32 abgr);

#endif
