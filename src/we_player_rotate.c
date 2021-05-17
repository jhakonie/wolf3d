#include "we_editor.h"

void	we_player_rotate(t_editor *e, t_u32 x, t_u32 y)
{
	static t_p2		prev;
	t_p2			curr;
	t_p2			rel;

	curr.x = (float)x - 0.5f * e->frame_buffer.width;
	rel.x = prev.x - curr.x;
	e->player.direction_d += rel.x;
	if (e->player.direction_d < 0.0)
		e->player.direction_d += 360.0;
	else if (e->player.direction_d > 360.0)
		e->player.direction_d -= 360.0;
	curr.y = (float)y - 0.5f * e->frame_buffer.height;
	rel.y = prev.y - curr.y;
	e->player.height += rel.y * 0.005f;
	if (e->player.height < 0)
		e->player.height = 0;
	if (e->player.height > WE_BLOCK_W)
		e->player.height = WE_BLOCK_W;
	prev = curr;
	e->draw = wx_true;
}
