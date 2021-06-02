#include "we_editor.h"
#include "wx_time.h"

static void	zz_integrate(t_editor *e)
{
	if (e->time.sim_time_accumulator_s >= e->time.sim_time_step_s)
	{
		e->player.position.x += e->player.move.forward.x;
		e->player.position.y += e->player.move.forward.y;
		e->player.position.x -= e->player.move.backward.x;
		e->player.position.y -= e->player.move.backward.y;
		e->player.position.x -= e->player.move.left.x;
		e->player.position.y -= e->player.move.left.y;
		e->player.position.x += e->player.move.right.x;
		e->player.position.y += e->player.move.right.y;
		e->time.sim_time_s += e->time.sim_time_step_s;
		e->time.sim_time_accumulator_s -= e->time.sim_time_step_s;
		wx_buffer_set(&e->player.move, sizeof(e->player.move), 0);
	}
}

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

static t_bool	zz_poll_event(t_editor *e)
{
	while (SDL_PollEvent(&e->event) != 0)
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
	t_f64		sim_delta_s;
	t_f64		real_time0_s;
	t_f64		real_time1_s;

	real_time0_s = e->time.sim_time_s;
	while (!e->quit)
	{
		real_time1_s = wx_time_s();
		sim_delta_s = wx_f64_min(real_time1_s - real_time0_s, 3.0
				* e->time.sim_time_step_s);
		real_time0_s = real_time1_s;
		e->time.sim_time_accumulator_s += sim_delta_s;
		if (e->map.draw_3d)
			e->quit = zz_poll_event(e);
		else
			e->quit = zz_wait_event(e);
		zz_integrate(e);
		if (e->draw)
		{
			we_draw(e);
			we_draw_to_window(e);
		}
	}
	return (wx_true);
}
