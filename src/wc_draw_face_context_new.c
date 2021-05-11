#include "wc_draw.h"

/*
** 2021-04-26 note: a "2d" edge function in screen space looks like:
** screen, pseudo-2d/3d omitting z-axis:
** +------------>x
** |        p0
** |         +
** |          \  (+ side)
** |           \    +p
** | (- side)   \
** |             +
** v             p1
** y
**     (p1->y - p0->y) * (p->x - p0->x) - (p1->x - p0->x) * (p->y - p0->y)
**
** shuffling it:
**     (p1->y - p0->y) * p->x + (p1->x + p0->x) * p->y +
**     (p1->x * p0->y - p1->y * p0->x)
**
** shows the x: (p1->y - p0->y), and y: (p1->x + p0->x) gradients
**
** from there for each edge the x- and y-steps for the face's u, v and w:
** u x_step = (p1->y - p0->y)
** u y_step = (p1->x + p0->x)
** v x_step = (p2->y - p1->y)
** v y_step = (p2->x + p1->x)
** w x_step = (p0->y - p2->y)
** w y_step = (p0->x + p2->x)
**
** which could be a faster way to update face_u, face_v, face_w and uvs per
** pixel rather than call zz_screen_area() three times per pixel
*/
t_draw_face_context	wc_draw_face_context_new(t_draw_context *dc,
	t_texture const *t)
{
	t_draw_face_context	dfc;

	dfc.fb = dc->frame_buffer;
	dfc.db = dc->depth_buffer;
	dfc.screen_positions = dc->buffers->screen_positions;
	dfc.uvs = dc->buffers->uvs;
	dfc.t = t;
	return (dfc);
}
