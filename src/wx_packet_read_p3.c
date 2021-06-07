#include "wx_net.h"

void	wx_packet_read_p3(t_packet *p, t_p3 *x)
{
	wx_packet_read_f32(p, &x->x);
	wx_packet_read_f32(p, &x->y);
	wx_packet_read_f32(p, &x->z);
}
