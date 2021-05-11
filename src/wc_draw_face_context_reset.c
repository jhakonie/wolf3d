#include "wc_draw.h"

void	wc_draw_face_context_reset(t_draw_face_context *dfc, t_u16 i0, t_u16 i1,
	t_u16 i2)
{
	dfc->uv0 = dfc->uvs + i0;
	dfc->uv1 = dfc->uvs + i1;
	dfc->uv2 = dfc->uvs + i2;
	dfc->p0 = dfc->screen_positions + i0;
	dfc->p1 = dfc->screen_positions + i1;
	dfc->p2 = dfc->screen_positions + i2;
	dfc->aabb = wc_screen_xy_aabb(dfc->p0, dfc->p1, dfc->p2, dfc->fb);
	dfc->view_z0 = 1.0f / dfc->p0->z;
	dfc->view_z1 = 1.0f / dfc->p1->z;
	dfc->view_z2 = 1.0f / dfc->p2->z;
}
