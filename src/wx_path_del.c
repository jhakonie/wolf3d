#include "stdlib.h"

#include "wx_path.h"

void	wx_path_del(t_path *p)
{
	free(p->buffer);
	p->buffer = WX_NULL;
	p->buffer_size = 0;
	p->path_size = 0;
}
