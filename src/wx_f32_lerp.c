#include "wx_types.h"

t_f32	wx_f32_lerp(t_f32 x0, t_f32 x1, t_f32 t)
{
	t_f32	x;

	x = x0 + t * (x1 - x0);
	return (x);
}
