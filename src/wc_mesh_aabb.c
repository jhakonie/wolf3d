#include "wc_draw.h"

void	wc_mesh_aabb(t_mesh *m)
{
	t_u64		i;

	m->aabb.max = (t_p3){-WX_F32_INF, -WX_F32_INF, -WX_F32_INF};
	m->aabb.min = (t_p3){WX_F32_INF, WX_F32_INF, WX_F32_INF};
	i = 0;
	while (i < m->vertices.size)
	{
		m->aabb.max.x = wx_f32_max(m->vertices.buffer[i].position.x,
				m->aabb.max.x);
		m->aabb.max.y = wx_f32_max(m->vertices.buffer[i].position.y,
				m->aabb.max.y);
		m->aabb.max.z = wx_f32_max(m->vertices.buffer[i].position.z,
				m->aabb.max.z);
		m->aabb.min.x = wx_f32_min(m->vertices.buffer[i].position.x,
				m->aabb.min.x);
		m->aabb.min.y = wx_f32_min(m->vertices.buffer[i].position.y,
				m->aabb.min.y);
		m->aabb.min.z = wx_f32_min(m->vertices.buffer[i].position.z,
				m->aabb.min.z);
		++i;
	}
}
