#include "we_editor.h"

static t_bool	zz_wait_event(t_editor *e)
{
	if (SDL_WaitEvent(&e->event) != 0)
	{
		if (e->event.type == SDL_QUIT)
			return (wx_true);
		else if (e->event.type == SDL_KEYDOWN)
		{
			if (e->event.key.keysym.sym == SDLK_ESCAPE)
				return (wx_true);
			else
				we_key_event(e->event.key.keysym.sym, e);
		}
		else if (e->event.type == SDL_WINDOWEVENT)
			we_window_event(e, &e->event.window);
		else if (e->event.type == SDL_MOUSEMOTION
			|| e->event.type == SDL_MOUSEBUTTONDOWN
			|| e->event.type == SDL_MOUSEBUTTONUP)
			we_mouse_event(e);
	}
	return (wx_false);
}

t_bool	we_editor_run(t_editor *e)
{
	while (!e->quit)
	{
		if (e->draw)
		{
			we_draw(e);
			we_draw_to_window(e);
		}
		e->quit = zz_wait_event(e);
	}
	return (wx_true);
}
