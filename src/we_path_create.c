#include "we_path.h"
#include "stdlib.h"

t_bool	we_path_create(t_path	*p, t_c8 *start, t_c8 *middle, t_c8 *end)
{
	if (!we_path_new(p, start))
	{
		p->buffer = WX_NULL;
		return (wx_false);
	}
	if (!we_path_add_back(p, middle)
		|| !we_path_add_back(p, end))
	{
		free(p->buffer);
		p->buffer = WX_NULL;
		return (wx_false);
	}
	return (wx_true);
}
