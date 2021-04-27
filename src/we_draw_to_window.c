#include "we_editor.h"

void	we_draw_to_window(t_editor *e)
{
	t_s32	*texture_data;
	t_s32	texture_pitch;

	if (SDL_LockTexture(e->texture, WX_NULL, (void **)&texture_data,
			&texture_pitch) < 0)
	{
		e->quit = wx_true;
	}
	wx_buffer_copy(texture_data, e->frame_buffer.data,
		e->frame_buffer.data_size);
	SDL_UnlockTexture(e->texture);
	if (SDL_RenderCopy(e->renderer, e->texture, WX_NULL, WX_NULL) < 0)
	{
		e->quit = wx_true;
	}
	SDL_RenderPresent(e->renderer);
}
