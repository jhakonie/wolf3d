#include "wc_draw.h"

/*
** 2021-05-21 todo: deduplicate and create wc_xxx() function?
*/
static void	zz_indices(t_u16s *is, t_u16 base_index)
{
	is->buffer[is->size + 0] = base_index + 0;
	is->buffer[is->size + 1] = base_index + 1;
	is->buffer[is->size + 2] = base_index + 2;
	is->buffer[is->size + 3] = base_index + 3;
	is->buffer[is->size + 4] = base_index + 2;
	is->buffer[is->size + 5] = base_index + 1;
	is->size += 6;
}

static t_bool	zz_is_northern_outter(t_map const *m, t_u32 x, t_u32 z)
{
	if (z == m->height - 1)
	{
		return (wx_false);
	}
	if (m->tiles[(z + 1) *m->width + x] == wc_map_tile_type_wall)
	{
		return (wx_false);
	}
	return (wx_true);
}

/*
** 2021-05-18 note: generate 2 triangles for the north-facing wall of a tile
**
**   v0          v2
**    +----------+
**    |        . |
** y  |      .   |
** ^  |    .     |
** |  |  .       |
** |  |.         |
** |  +----------+
** | v1          v3
** +------->x
** z
*/
static void	zz_add_north_wall(t_map_mesh *mm, t_u32 x, t_u32 z, t_map const *m)
{
	t_vertex	*vs;

	zz_indices(&mm->north.indices, mm->north.vertices.size);
	vs = mm->north.vertices.buffer + mm->north.vertices.size;
	vs[0].position = (t_p3){x * m->tile_width, m->wall_height, z * m->tile_width
		+ m->tile_width};
	vs[0].normal = (t_n3){0.0f, 0.0f, 1.0f};
	vs[0].uv = (t_p2){0.0f, 0.0f};
	vs[1].position = (t_p3){x * m->tile_width, 0.0f, z * m->tile_width
		+ m->tile_width};
	vs[1].normal = (t_n3){0.0f, 0.0f, 1.0f};
	vs[1].uv = (t_p2){0.0f, 1.0f};
	vs[2].position = (t_p3){x * m->tile_width + m->tile_width, m->wall_height,
		z * m->tile_width + m->tile_width};
	vs[2].normal = (t_n3){0.0f, 0.0f, 1.0f};
	vs[2].uv = (t_p2){1.0f, 0.0f};
	vs[3].position = (t_p3){x * m->tile_width + m->tile_width, 0.0f,
		z * m->tile_width + m->tile_width};
	vs[3].normal = (t_n3){0.0f, 0.0f, 1.0f};
	vs[3].uv = (t_p2){1.0f, 1.0f};
	mm->north.vertices.size += 4;
}

t_bool	wc_map_mesh_new_from_map_north(t_map_mesh *mm, t_map const *m)
{
	t_u32	x;
	t_u32	z;

	if (!wc_u16s_new(&mm->north.indices, m->width * m->height * 6)
		|| !wc_vertices_new(&mm->north.vertices, m->width * m->height * 4))
	{
		return (wx_false);
	}
	z = 0;
	while (z < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			if (m->tiles[z * m->width + x] == wc_map_tile_type_wall
				&& zz_is_northern_outter(m, x, z))
			{
				zz_add_north_wall(mm, x, z, m);
			}
			++x;
		}
		++z;
	}
	wc_mesh_aabb(&mm->north);
	return (wx_true);
}
