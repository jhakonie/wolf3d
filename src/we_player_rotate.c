#include "we_editor.h"

void	we_player_rotate(t_editor *e, t_u32 x, t_u32 y)
{
	static t_p2		previous;
	t_p2			current;
	t_p2			relative;

	current.x = (float)x - 0.5f * e->frame_buffer.width;
	current.y = (float)y - 0.5f * e->frame_buffer.height;
	if (e->map.draw_3d)
	{
		relative.x = previous.x - current.x;
		e->player.direction_d += relative.x;
		if (e->player.direction_d < 0.0)
			e->player.direction_d += 360.0;
		else if (e->player.direction_d > 360.0)
			e->player.direction_d -= 360.0;
		relative.y = previous.y - current.y;
		e->player.height += relative.y * 0.005f;
		if (e->player.height < 0)
			e->player.height = 0;
		else if (e->player.height > 1)
			e->player.height = 1;
	}
	previous = current;
	e->draw = wx_true;
}
