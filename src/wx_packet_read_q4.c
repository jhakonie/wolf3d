#include "wx_net.h"

void	wx_packet_read_q4(t_packet *p, t_u64 *i, t_q4 *x)
{
	wx_packet_read_f32(p, i, &x->x);
	wx_packet_read_f32(p, i, &x->y);
	wx_packet_read_f32(p, i, &x->z);
	wx_packet_read_f32(p, i, &x->w);
}
