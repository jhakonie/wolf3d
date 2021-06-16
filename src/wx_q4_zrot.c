#include "wx_math.h"

t_f32	wx_q4_zrot(t_q4 const *q)
{
	t_f32	c0;
	t_f32	c1;
	t_f32	zrot;

	c0 = 2 * (q->x * q->y + q->w * q->z);
	c1 = q->w * q->w - q->x * q->x + q->y * q->y - q->z * q->z;
	zrot = atan2(c0, c1);
	return (zrot);
}
