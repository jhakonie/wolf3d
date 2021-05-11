#include "wc_draw.h"

/*
** 2021-04-08 todo: clamping to [0.0f, width] and [0.0f, height] introduces
** some inaccuracy? does there need to be some sort of +/-0.5f offsets?
**
** 2021-04-26 todo: really need to think how to properly be pixel-accurate here.
** the vertex coordinates will not usually hit pixel centers
*/
t_rectangle	wc_screen_xy_aabb(t_p3 const *p0, t_p3 const *p1, t_p3 const *p2,
				t_frame_buffer const *fb)
{
	t_rectangle	r;

	r.p0.x = wx_f32_max(0.0f, wx_f32_min(wx_f32_min(p0->x, p1->x), p2->x));
	r.p0.y = wx_f32_max(0.0f, wx_f32_min(wx_f32_min(p0->y, p1->y), p2->y));
	r.p1.x = wx_f32_min(wx_f32_max(wx_f32_max(p0->x, p1->x), p2->x),
			fb->width);
	r.p1.y = wx_f32_min(wx_f32_max(wx_f32_max(p0->y, p1->y), p2->y),
			fb->height);
	return (r);
}
