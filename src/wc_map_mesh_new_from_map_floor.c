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

/*
** 2021-05-18 note: generate 2 triangles for the floor tile on the xz-plane
** y
** +------->x
** | v3          v1
** |  +----------+
** |  |        . |
** |  |      .   |
** v  |    .     |
** z  |  .       |
**    |.         |
**    +----------+
**   v2          v0
*/
static void	zz_add_floor_tile(t_map_mesh *mm, t_u32 x, t_u32 z, t_f32 width)
{
	t_vertex	*vs;

	zz_indices(&mm->floor.indices, mm->floor.vertices.size);
	vs = mm->floor.vertices.buffer + mm->floor.vertices.size;
	vs[0].position = (t_p3){x * width + width, 0.0f, z * width + width};
	vs[0].normal = (t_n3){0.0f, 1.0f, 0.0f};
	vs[0].uv = (t_p2){0.0f, 0.0f};
	vs[1].position = (t_p3){x * width + width, 0.0f, z * width};
	vs[1].normal = (t_n3){0.0f, 1.0f, 0.0f};
	vs[1].uv = (t_p2){0.0f, 1.0f};
	vs[2].position = (t_p3){x * width, 0.0f, z * width + width};
	vs[2].normal = (t_n3){0.0f, 1.0f, 0.0f};
	vs[2].uv = (t_p2){1.0f, 0.0f};
	vs[3].position = (t_p3){x * width, 0.0f, z * width};
	vs[3].normal = (t_n3){0.0f, 1.0f, 0.0f};
	vs[3].uv = (t_p2){1.0f, 1.0f};
	mm->floor.vertices.size += 4;
}

t_bool	wc_map_mesh_new_from_map_floor(t_map_mesh *mm, t_map const *m)
{
	t_u32	x;
	t_u32	z;

	if (!wc_u16s_new(&mm->floor.indices, m->width * m->height * 6)
		|| !wc_vertices_new(&mm->floor.vertices, m->width * m->height * 4))
		return (wx_false);
	z = 0;
	while (z < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			if (m->tiles[z * m->width + x] == WX_MAP_TILE_TYPE_FLOOR
				|| m->tiles[z * m->width + x]
				== WX_MAP_TILE_TYPE_PLAYER_SPAWN
				|| m->tiles[z * m->width + x] == WX_MAP_TILE_TYPE_DOOR)
			{
				zz_add_floor_tile(mm, x, z, m->tile_width);
			}
			++x;
		}
		++z;
	}
	wc_mesh_aabb(&mm->floor);
	return (wx_true);
}
