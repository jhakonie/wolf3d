#include "wx_math.h"

t_q4	wx_q4_mul_q4(const t_q4 *l, const t_q4 *r)
{
	t_q4	q;

	q.x = (l->x * r->w) + (l->y * r->z) - (l->z * r->y) + (l->w * r->x);
	q.y = (l->y * r->w) + (l->z * r->x) + (l->w * r->y) - (l->x * r->z);
	q.z = (l->z * r->w) + (l->w * r->z) + (l->x * r->y) - (l->y * r->x);
	q.w = (l->w * r->w) - (l->x * r->x) - (l->y * r->y) - (l->z * r->z);
	return (q);
}
