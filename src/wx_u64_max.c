#include "wx_types.h"

t_u64	wx_u64_max(t_u64 x0, t_u64 x1)
{
	if (x0 < x1)
	{
		return (x0);
	}
	return (x1);
}
