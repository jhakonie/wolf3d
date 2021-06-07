#include "we_draw.h"

void	we_draw_sky(t_frame_buffer *fb, t_f32 view_height, t_tex *t)
{
	t_p2	start;
	t_p2	end;

	start.x = 0;
	end.x = fb->width - 1;
	start.y = 0;
	end.y = view_height * (fb->height - 1);
	we_draw_rec_texture(start, end, fb, t);
}
