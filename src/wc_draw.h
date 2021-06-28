/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 23:38:47 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/06/28 23:59:55 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WC_DRAW_H
# define WC_DRAW_H

# include "wx_frame_buffer.h"
# include "wx_math.h"
# include "wx_draw.h"

typedef struct s_client				t_client;

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

/*
** 2021-05-06 todo: out_indices and _size are slighty misleading names as "out"
** could be understod to mean they are outside a clipping plane. "out" means the
** index is part of the output/result. come up with a better name
*/
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

struct	s_depth_buffer
{
	t_f32	*data;
	t_u64	data_size;
	t_u32	width;
	t_u32	height;
};
typedef struct s_depth_buffer		t_depth_buffer;

t_bool				wc_depth_buffer_new(t_depth_buffer *db, t_u32 width,
						t_u32 height);
void				wc_depth_buffer_del(t_depth_buffer *db);
t_f32				wc_depth_buffer_get(t_depth_buffer *db, t_f32 x, t_f32 y);
void				wc_depth_buffer_set(t_depth_buffer *db, t_f32 x, t_f32 y,
						t_f32 d);

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

t_bool				wc_u16s_new(t_u16s *c, t_u64 buffer_size);
void				wc_u16s_del(t_u16s *c);
t_bool				wc_u16s_add_back(t_u16s *c, t_u16 v);

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

t_bool				wc_vertices_new(t_vertices *c, t_u64 buffer_size);
void				wc_vertices_del(t_vertices *c);
t_bool				wc_vertices_add_back(t_vertices *c, t_vertex const *v);

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

t_bool				wc_mesh_new_from_file(t_mesh *m, char const *filename);
void				wc_mesh_del(t_mesh *m);
void				wc_mesh_aabb(t_mesh *m);

/*
**
*/
struct	s_map_mesh
{
	t_mesh		floor;
	t_mesh		north;
	t_mesh		east;
	t_mesh		west;
	t_mesh		south;
};
typedef struct s_map_mesh			t_map_mesh;

t_bool				wc_map_mesh_new_from_map(t_map_mesh *mm, t_map const *m);
t_bool				wc_map_mesh_new_from_map_east(t_map_mesh *mm,
						t_map const *m);
t_bool				wc_map_mesh_new_from_map_floor(t_map_mesh *mm,
						t_map const *m);
t_bool				wc_map_mesh_new_from_map_north(t_map_mesh *mm,
						t_map const *m);
t_bool				wc_map_mesh_new_from_map_south(t_map_mesh *mm,
						t_map const *m);
t_bool				wc_map_mesh_new_from_map_west(t_map_mesh *mm,
						t_map const *m);
void				wc_map_mesh_del(t_map_mesh *mm);

/*
** 2021-04-20 todo: decide whether to keep screen_positions as t_p3 or make a
** new specific type for them, with less confusing names for the members. right
** now screen_position.z stores 1.0f/view_position.z confusingly enough
*/
struct	s_pipeline_buffers
{
	t_p3	*screen_positions;
	t_u64	screen_positions_size;
	t_p2	*uvs;
	t_u64	uvs_size;
	t_p3	*view_positions;
	t_u64	view_positions_size;
	t_u16	*visible_indices;
	t_u64	visible_indices_size;
};
typedef struct s_pipeline_buffers	t_pipeline_buffers;

t_bool				wc_pipeline_buffers_new(t_pipeline_buffers *pb);
void				wc_pipeline_buffers_del(t_pipeline_buffers *pb);

struct	s_draw_context
{
	t_pipeline_buffers	*buffers;
	t_m44				clip_from_view;
	t_frame_buffer		*frame_buffer;
	t_depth_buffer		*depth_buffer;
	t_frustum			frustum;
	t_m44				view_from_object;
};
typedef struct s_draw_context		t_draw_context;

struct	s_rectangle
{
	t_p2	p0;
	t_p2	p1;
};
typedef struct s_rectangle			t_rectangle;

/*
** 2021-05-07 todo: consider the need for view_z0, _z1, _z2 members. possible
** alternative could be that screen positions' .z is already view_z or include
** both: view_z and inv_view_z in "screen positions". possibly meaning
** switching from p3 to p4 or creating a whole new type for the mixed screen and
** view coordinate combination
*/
struct	s_draw_face_context
{
	t_frame_buffer	*fb;
	t_depth_buffer	*db;
	t_texture const	*t;
	t_p3 const		*screen_positions;
	t_p2 const		*uvs;
	t_p3 const		*screen_p0;
	t_p3 const		*screen_p1;
	t_p3 const		*screen_p2;
	t_rectangle		aabb;
	t_p2 const		*uv0;
	t_p2 const		*uv1;
	t_p2 const		*uv2;
	t_f32			screen_a0;
	t_f32			screen_a1;
	t_f32			screen_a2;
	t_f32			inv_a;
	t_f32			view_b0;
	t_f32			view_b1;
	t_f32			view_b2;
	t_f32			view_z0;
	t_f32			view_z1;
	t_f32			view_z2;
	t_p3			p;
	t_f32			p_inv_view_z;
	t_f32			texture_u;
	t_f32			texture_v;
};
typedef struct s_draw_face_context	t_draw_face_context;

t_draw_face_context	wc_draw_face_context_new(t_draw_context *dc,
						t_texture const *t);
void				wc_draw_face_context_reset(t_draw_face_context *dfc,
						t_u16 i0, t_u16 i1, t_u16 i2);

void				wc_draw_25d(t_client *c);
void				wc_draw_25d_enemy(t_frame_buffer *fb, t_ray *ray,
						t_texture *texture);
void				wc_draw_3d(t_client *c);
void				wc_draw_add_visible(t_draw_context *dc,
						t_clip_context const *cc);
void				wc_draw_clip(t_draw_context *dc, t_face const *f,
						t_plane const *p);
void				wc_draw_copy(t_client *c, t_frame_buffer const *fb);
void				wc_draw_face(t_draw_face_context *dfc);
void				wc_draw_mesh(t_draw_context *dc, t_mesh const *m,
						t_texture const *t);
void				wc_draw_rectangle_outline(t_frame_buffer *fb, t_p3 p,
						t_f32 width, t_u32 abgr);
void				wc_draw_rectangle_solid(t_frame_buffer *fb, t_p3 p,
						t_f32 width, t_u32 abgr);

t_bool				wc_map_new_from_file(t_map *m, char const *filename);

t_p2				wc_p2_lerp(t_p2 const *p0, t_p2 const *p1, t_f32 t);

t_p3				wc_p3_lerp(t_p3 const *p0, t_p3 const *p1, t_f32 t);

t_rectangle			wc_screen_xy_aabb(t_p3 const *p0, t_p3 const *p1,
						t_p3 const *p2, t_frame_buffer const *fb);
t_f32				wc_screen_xy_area(t_p3 const *p0, t_p3 const *p1,
						t_p3 const *p2);

t_bool				wc_texture_new_from_file(t_texture *t,
						char const *filename);
void				wc_texture_del(t_texture *t);
t_u32				wc_texture_get(t_texture const *t, t_f32 u, t_f32 v);

#endif
