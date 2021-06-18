#include "we_editor.h"

void	we_init_map(t_map_view *m, t_u32 win_w, t_u32 win_h)
{
	m->grid.divide = WX_MAP_TILES_WIDTH;
	m->grid.start.x = (win_w - 1) / 8;
	m->grid.start.y = 0;
	m->grid.end.x = win_w - 1;
	m->grid.end.y = win_h - 1;
	m->grid.part.x = (m->grid.end.x - m->grid.start.x)
		/ m->grid.divide;
	m->grid.part.y = m->grid.end.y / m->grid.divide;
	m->tile_count = WX_MAP_TILES_WIDTH * WX_MAP_TILES_WIDTH;
	m->ptr_draw = wx_false;
	m->ptr_clear = wx_false;
	m->ptr.x = 0;
	m->ptr.y = 0;
	m->ptr_hold = wx_false;
	m->draw_rays = wx_false;
	m->grid.color[0] = 0xAAB0AF;
	m->grid.color[1] = 0x0000FF;
}
