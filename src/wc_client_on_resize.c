#include "wc_client.h"

/*
** SDL_DestroyRenderer() frees related textures
*/
void	wc_client_on_resize(t_client *c, t_s32 width, t_s32 height)
{
	SDL_DestroyRenderer(c->renderer);
	c->renderer = SDL_CreateRenderer(c->window, -1, 0);
	if (!c->renderer)
	{
		c->run = wx_false;
	}
	c->texture = SDL_CreateTexture(c->renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, width, height);
	if (!c->texture)
	{
		c->run = wx_false;
	}
	free(c->frame_buffer.data);
	c->frame_buffer.data = WX_NULL;
	c->frame_buffer.data_size = width * height * 4;
	c->frame_buffer.data = (t_u8 *)malloc(c->frame_buffer.data_size);
	if (!c->frame_buffer.data)
	{
		c->run = wx_false;
	}
	wx_buffer_set(c->frame_buffer.data, c->frame_buffer.data_size, 0);
	c->frame_buffer.width = width;
	c->frame_buffer.height = height;
}
