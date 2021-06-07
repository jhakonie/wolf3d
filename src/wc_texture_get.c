#include "wc_draw.h"

/* static t_f32	zz_f32_clamp(t_f32 v, t_f32 low, t_f32 high) */
/* { */
/*	if (v < low) */
/*	{ */
/*		return (low); */
/*	} */
/*	if (v > high) */
/*	{ */
/*		return (high); */
/*	} */
/*	return v; */
/* } */

/*
** 2021-05-06 todo: work out the proper way to map from [0, 1] to [0, width - 1]
** and [0, 1] to [0, height - 1]
**
** 2021-05-06 todo: double check how the rgba color components are laid out in
** memory for the t->buffer, expected:
** low      high
** rr gg bb aa
**
** looks like:
** low      high
** bb gg rr aa
**
** which is slightly surprising
**
** 2021-05-06 todo: decide what to do with u. it seems at least blender exports
** uv coordinates so that bottom-left is [0,0] and top-right is [1,1]. could
** flip the v-axis:
**     v = 1.0f - v;
** needs to agree with wc_parse_obj_uv() and wc_map_mesh_new_from_map_*()
** functions generate uvs
**
** 2021-06-01 todo: we're getting uv coordinates outside [0.0f, 1.0f], so
** just clamp them?
*/
t_u32	wc_texture_get(t_texture const *t, t_f32 u, t_f32 v)
{
	t_u32	c;
	t_u64	i;
	t_u32	u_;
	t_u32	v_;

	u_ = u * (t->width - 1);
	v_ = v * (t->height - 1);
	i = 4 * (v_ * t->width + u_);
	c = t->buffer[i + 0] << 16;
	c |= t->buffer[i + 1] << 8;
	c |= t->buffer[i + 2] << 0;
	c |= t->buffer[i + 3] << 24;
	return (c);
}
