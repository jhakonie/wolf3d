#include "stdlib.h"

#include "wx_path.h"

t_bool	wx_path_new3(t_path	*p, t_c8 const *start,
	t_c8 const *middle, t_c8 const *end)
{
	if (!wx_path_new(p, start))
	{
		p->buffer = WX_NULL;
		return (wx_false);
	}
	if (!wx_path_add_back(p, middle))
	{
		wx_path_del(p);
		return (wx_false);
	}
	if (!wx_path_add_back(p, end))
	{
		wx_path_del(p);
		return (wx_false);
	}
	return (wx_true);
}
