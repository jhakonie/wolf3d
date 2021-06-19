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
	while (y < WX_MAP_TILES_WIDTH)
	{
		x = 0;
		while (x < WX_MAP_TILES_WIDTH)
		{
			m->tiles[i] = WE_ID_INIT;
			i++;
			x++;
		}
		y++;
	}
}
