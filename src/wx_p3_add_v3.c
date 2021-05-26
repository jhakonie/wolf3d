#include "wx_math.h"

t_p3	wx_p3_add_v3(t_p3 const *l, t_v3 const *r)
{
	t_p3	p;

	p = (t_p3){l->x + r->x, l->y + r->y, l->z + r->z};
	return (p);
}
