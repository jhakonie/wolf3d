#include "wx_math.h"

t_p2	wc_p2_lerp(t_p2 const *p0, t_p2 const *p1, t_f32 t)
{
	t_p2	p;

	p.x = p0->x + t * (p1->x - p0->x);
	p.y = p0->y + t * (p1->y - p0->y);
	return (p);
}
