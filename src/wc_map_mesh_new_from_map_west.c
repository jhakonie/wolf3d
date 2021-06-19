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

static t_bool	zz_is_western_outter(t_map const *m, t_u32 x, t_u32 z)
{
	if (x == m->width - 1)
	{
		return (wx_false);
	}
	if (m->tiles[z * m->width + (x + 1)] == WX_MAP_TILE_TYPE_WALL)
	{
		return (wx_false);
	}
	return (wx_true);
}

/*
** 2021-05-18 note: generate 2 triangles for the west-facing wall of a tile
**
**  v0          v2
**   +----------+
**   |        . |
**   |      .   |  y
**   |    .     |  ^
**   |  .       |  |
**   |.         |  |
**   +----------+  |
**  v1          v3 |
**        z<-------+
**                 x
*/
static void	zz_add_west_wall(t_map_mesh *mm, t_u32 x, t_u32 z, t_map const *m)
{
	t_vertex	*vs;

	zz_indices(&mm->west.indices, mm->west.vertices.size);
	vs = mm->west.vertices.buffer + mm->west.vertices.size;
	vs[0].position = (t_p3){x * m->tile_width + m->tile_width, m->wall_height,
		z * m->tile_width + m->tile_width};
	vs[0].normal = (t_n3){1.0f, 0.0f, 0.0f};
	vs[0].uv = (t_p2){0.0f, 0.0f};
	vs[1].position = (t_p3){x * m->tile_width + m->tile_width, 0.0f,
		z * m->tile_width + m->tile_width};
	vs[1].normal = (t_n3){1.0f, 0.0f, 0.0f};
	vs[1].uv = (t_p2){0.0f, 1.0f};
	vs[2].position = (t_p3){x * m->tile_width + m->tile_width, m->wall_height,
		z * m->tile_width};
	vs[2].normal = (t_n3){1.0f, 0.0f, 0.0f};
	vs[2].uv = (t_p2){1.0f, 0.0f};
	vs[3].position = (t_p3){x * m->tile_width + m->tile_width, 0.0f,
		z * m->tile_width};
	vs[3].normal = (t_n3){1.0f, 0.0f, 0.0f};
	vs[3].uv = (t_p2){1.0f, 1.0f};
	mm->west.vertices.size += 4;
}

t_bool	wc_map_mesh_new_from_map_west(t_map_mesh *mm, t_map const *m)
{
	t_u32	x;
	t_u32	z;

	if (!wc_u16s_new(&mm->west.indices, m->width * m->height * 6)
		|| !wc_vertices_new(&mm->west.vertices, m->width * m->height * 4))
	{
		return (wx_false);
	}
	z = 0;
	while (z < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			if (m->tiles[z * m->width + x] == WX_MAP_TILE_TYPE_WALL
				&& zz_is_western_outter(m, x, z))
			{
				zz_add_west_wall(mm, x, z, m);
			}
			++x;
		}
		++z;
	}
	wc_mesh_aabb(&mm->west);
	return (wx_true);
}
