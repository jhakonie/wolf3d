#include "wx_net.h"

void	wx_packet_write_u64(t_packet *p, t_u64 x)
{
	wx_buffer_copy(p->buffer + p->size, &x, sizeof(x));
	p->size += sizeof(x);
}
