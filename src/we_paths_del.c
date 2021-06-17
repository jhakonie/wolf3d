#include "we_editor.h"

t_bool	we_paths_del(t_path *p, t_u32 size)
{
	t_u32	i;

	i = 0;
	while (i < size)
	{
		wx_path_del(&p[i]);
		i++;
	}
	return (wx_false);
}
