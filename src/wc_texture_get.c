#include "wc_draw.h"

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
** uv coordinates so that 0,0 is at bottom left, 1,1 at top right. just flip the
** input v-axis for now:
*/
t_u32	wc_texture_get(t_texture const *t, t_f32 u, t_f32 v)
{
	t_u32	c;
	t_u64	i;

	v = 1.0f - v;
	i = 4 * ((t_u32)(v * t->height) * t->width + (t_u32)(u * t->width));
	c = t->buffer[i + 0] << 16;
	c |= t->buffer[i + 1] << 8;
	c |= t->buffer[i + 2] << 0;
	c |= t->buffer[i + 3] << 24;
	return (c);
}
