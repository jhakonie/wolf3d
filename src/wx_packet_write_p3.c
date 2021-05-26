#include "wx_net.h"

void	wx_packet_write_p3(t_packet *p, t_p3 const *x)
{
	wx_packet_write_f32(p, x->x);
	wx_packet_write_f32(p, x->y);
	wx_packet_write_f32(p, x->z);
}
