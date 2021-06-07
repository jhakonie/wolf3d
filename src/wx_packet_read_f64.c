#include "wx_net.h"

void	wx_packet_read_f64(t_packet *p, t_f64 *x)
{
	wx_buffer_copy(x, p->buffer + p->read_i, sizeof(*x));
	p->read_i += sizeof(*x);
}
