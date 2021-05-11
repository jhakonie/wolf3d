#include "wc_draw.h"

/*
** 2021-04-09 note:
** the area in screen space on the xy plane of the projected face
** screen, pseudo-2d/3d omitting z-axis:
** +------------>x
** |   p0       p2
** |    +-------+
** |     \     /
** |      \   /
** |       \ /
** |        +
** v        p1
** y
*/
t_f32	wc_screen_xy_area(t_p3 const *p0, t_p3 const *p1, t_p3 const *p2)
{
	t_f32	a;

	a = 0.5f * ((p1->y - p0->y) * (p2->x - p0->x) - (p1->x - p0->x)
			* (p2->y - p0->y));
	return (a);
}
