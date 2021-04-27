#include "we_editor.h"

t_bool	zz_update_tool_state(t_tool *t, t_u32 *draw, t_u32 x, t_u32 y)
{
	if (t->pre_selected && !t->selected)
	{
		t->selected = wx_true;
		t->pre_selected = wx_false;
		*draw = wx_true;
		return (wx_true);
	}
	else if (t->selected && x >= t->button.start.x && x <= t->button.end.x
		&& y >= t->button.start.y && y <= t->button.end.y)
	{
		t->selected = wx_false;
		t->pre_selected = wx_true;
		*draw = wx_true;
	}
	return (wx_false);
}

void	we_mouse_pos_tool_on_click(t_editor *e, t_u32 x, t_u32 y)
{
	t_u32	i;
	t_u32	tool_is_selected;

	i = 1;
	while (i < WE_TOOL_COUNT)
	{
		tool_is_selected = zz_update_tool_state(&e->tools.tool[i],
				&e->draw, x, y);
		if (tool_is_selected && e->tools.id != i)
		{
			e->tools.tool[e->tools.id].selected = wx_false;
			e->tools.tool[e->tools.id].pre_selected = wx_false;
			e->tools.id = i;
		}
		else if (!tool_is_selected && e->tools.tool[i].pre_selected)
			e->tools.id = WE_ID_INIT;
		if (e->tools.id == WE_TOOL_COUNT - 1)
			we_save_map_to_file(e);
		i++;
	}
}

t_bool	we_mouse_pos_tool(t_tool *t, t_u32 *draw, t_u32 x, t_u32 y)
{
	if (x >= t->button.start.x && x <= t->button.end.x
		&& y >= t->button.start.y && y <= t->button.end.y)
	{
		t->pre_selected = wx_true;
		*draw = wx_true;
	}
	if (x <= t->button.start.x || x >= t->button.end.x
		|| y <= t->button.start.y || y >= t->button.end.y)
	{
		t->pre_selected = wx_false;
		*draw = wx_true;
		return (wx_false);
	}
	return (wx_true);
}
