#include "we_draw.h"

void	we_draw_clip(t_p2 *p, t_frame_buffer *fb)
{
	if ((*p).x < 0)
		(*p).x = 0;
	else if ((*p).x >= fb->width)
		(*p).x = fb->width - 1;
	if ((*p).y < 0)
		(*p).y = 0;
	else if ((*p).y >= fb->height)
		(*p).y = fb->height - 1;
}
