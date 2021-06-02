#include "we_editor.h"

static void	zz_mouse_event_button_up(t_bool *ptr_hold, int event)
{
	if (event == SDL_BUTTON_LEFT)
		*ptr_hold = wx_false;
}

static void	zz_mouse_event_move(t_editor *e, t_u32 x, t_u32 y)
{
	t_u32	i;

	i = 1;
	we_player_rotate(e, x, y);
	if (x < e->map.grid.start.x)
	{
		e->map.ptr_draw = wx_false;
		e->map.ptr_clear = wx_true;
		while (i < WE_TOOL_COUNT)
		{
			we_mouse_pos_tool(&e->tools.tool[i], &e->draw, x, y);
			i++;
		}
	}
	else
		we_mouse_pos_grid(e, x, y);
}

static void	zz_mouse_event_button_down(t_editor *e, t_u32 x, t_u32 y)
{
	if (e->event.button.button == SDL_BUTTON_LEFT)
	{
		if (x < e->map.grid.start.x)
			we_mouse_pos_tool_on_click(e, x, y);
		else if (!e->map.draw_3d && e->tools.id != WE_ID_INIT)
			we_mouse_pos_grid_on_click(e, x, y);
	}
}

void	we_mouse_event(t_editor *e)
{
	if (e->map.draw_3d && e->event.type == SDL_MOUSEMOTION)
		zz_mouse_event_move(e, e->event.motion.x, e->event.motion.y);
	else if (!e->map.draw_3d && e->event.type == SDL_MOUSEMOTION)
		zz_mouse_event_move(e, e->event.motion.x, e->event.motion.y);
	else if (e->event.type == SDL_MOUSEBUTTONDOWN)
		zz_mouse_event_button_down(e, e->event.button.x, e->event.button.y);
	else if (e->event.type == SDL_MOUSEBUTTONUP)
		zz_mouse_event_button_up(&e->map.ptr_hold, e->event.button.button);
}
