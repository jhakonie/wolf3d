#include "wx_math.h"

t_v3	wx_q4_rot_v3(t_q4 const *q, t_v3 const *v)
{
	t_q4	cq;
	t_v3	rv;
	t_q4	vq;

	cq = (t_q4){-q->x, -q->y, -q->z, q->w};
	vq = (t_q4){v->x, v->y, v->z, 0.0f};
	vq = wx_q4_mul_q4(&vq, &cq);
	vq = wx_q4_mul_q4(q, &vq);
	rv = (t_v3){vq.x, vq.y, vq.z};
	return (rv);
}
