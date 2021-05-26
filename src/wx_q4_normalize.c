#include "wx_math.h"

void	wx_q4_normalize(t_q4 *q)
{
	t_f32	inv_n;

	inv_n = 1.0f / sqrtf(q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w);
	q->x = inv_n * q->x;
	q->y = inv_n * q->y;
	q->z = inv_n * q->z;
	q->w = inv_n * q->w;
}
