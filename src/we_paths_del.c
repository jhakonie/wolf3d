#include "we_editor.h"

t_bool	we_paths_del(t_path *p)
{
	t_u32	i;

	i = 0;
	while (i < WE_RESOURCES_COUNT)
	{
		we_path_del(&p[i]);
		i++;
	}
	return (wx_false);
}
