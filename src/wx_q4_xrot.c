#include "wx_math.h"

t_f32	wx_q4_xrot(t_q4 const *q)
{
	t_f32	c0;
	t_f32	xrot;

	c0 = -2 * (q->y * q->z - q->w * q->x);
	xrot = asin(c0);
	return (xrot);
}
