#include "we_editor.h"

t_bool	we_toolbar_icons_del(t_tool *t)
{
	t_u32	i;

	i = 1;
	while (i < WE_TOOL_COUNT)
	{
		free(t[i].button.icon.texture);
		i++;
	}
	return (wx_false);
}
