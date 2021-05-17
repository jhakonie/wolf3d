#include "we_editor.h"

/*
** Initializes map_tile types and sets their coordinates.
*/
void	we_tiles_set(t_map *m)
{
	t_u32		i;
	t_u32		x;
	t_u32		y;

	i = 0;
	y = 0;
	while (y < WE_GRID_DIVIDE)
	{
		x = 0;
		while (x < WE_GRID_DIVIDE)
		{
			m->tiles[i].id = WE_ID_INIT;
			m->tiles[i].block.x = x;
			m->tiles[i].block.y = y;
			i++;
			x++;
		}
		y++;
	}
}
