#include "we_editor.h"

void	we_level_del(t_level *l)
{
	we_paths_del(l->paths, WE_RESOURCES_COUNT);
	we_textures_del(&l->map.textures);
	l->name = WX_NULL;
}
