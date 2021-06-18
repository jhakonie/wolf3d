#include "we_editor.h"

t_bool	we_level_new(t_level *l)
{
	wx_buffer_set(l->paths, sizeof(*l->paths), 0);
	if (!we_paths_new(l->paths, l->name))
		return (wx_false);
	wx_buffer_set(&l->map.textures, sizeof(t_map_textures), 0);
	if (!we_textures_new(&l->map.textures, l->paths))
	{
		we_paths_del(l->paths, WE_RESOURCES_COUNT);
		return (wx_false);
	}
	return (wx_true);
}
