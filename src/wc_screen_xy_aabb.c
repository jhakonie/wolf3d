#include "math.h"

#include "wc_draw.h"

/*
** 2021-06-28 note: ceilf() the p0 gets us situated nicely on pixel centers.
** seems to avoid cracks so let's go with that. what could go wrong?
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
	r.p0.x = ceilf(r.p0.x - 0.5);
	r.p0.y = ceilf(r.p0.y - 0.5);
	return (r);
}
