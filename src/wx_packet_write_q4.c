#include "wx_net.h"

void	wx_packet_write_q4(t_packet *p, t_q4 const *x)
{
	wx_packet_write_f32(p, x->x);
	wx_packet_write_f32(p, x->y);
	wx_packet_write_f32(p, x->z);
	wx_packet_write_f32(p, x->w);
}
