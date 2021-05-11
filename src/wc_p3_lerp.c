#include "wx_math.h"

t_p3	wc_p3_lerp(t_p3 const *p0, t_p3 const *p1, t_f32 t)
{
	t_p3	p;

	p.x = p0->x + t * (p1->x - p0->x);
	p.y = p0->y + t * (p1->y - p0->y);
	p.z = p0->z + t * (p1->z - p0->z);
	return (p);
}
