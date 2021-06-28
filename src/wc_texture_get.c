#include "wc_draw.h"

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
