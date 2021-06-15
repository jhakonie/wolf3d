#include "we_editor.h"

void	we_draw_rec_frame(t_p2 start, t_p2 end, t_frame_buffer *fb, t_u32 c)
{
	t_p2	up;
	t_p2	down;

	if (start.y < 0)
		start.y = 0;
	if (start.x < 0)
		start.x = 0;
	if (end.x >= fb->width)
		end.x = fb->width - 1;
	if (end.y >= fb->height)
		end.y = fb->height - 1;
	up.x = end.x;
	up.y = start.y;
	down.x = start.x;
	down.y = end.y;
	we_draw_line(start, up, fb, c);
	we_draw_line(start, down, fb, c);
	we_draw_line(up, end, fb, c);
	we_draw_line(down, end, fb, c);
}
