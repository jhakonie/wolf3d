#include "wc_draw.h"
#include "wc_client.h"
#include "wx_draw.h"

/*
** 2021-05-15 todo: draw map using raycast
*/
void	wc_draw_25d(t_client *c)
{
	t_player	p;

	wx_buffer_set(c->frame_buffer.data, c->frame_buffer.data_size, 0);
	p.fov_d = 60;
	p.direction_d = wx_to_degrees(wx_q4_yrot(&c->player_orientation));
	p.direction_d -= 90;
	p.height = 0.5f;
	p.position.x = c->player_position.x;
	p.position.y = c->player_position.z;
	wx_draw_3d(&c->frame_buffer, p, &c->map);
	wc_draw_copy(c, &c->frame_buffer);
}
