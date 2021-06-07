#include "we_editor.h"

t_bool	we_level_new(t_level *l)
{
	wx_buffer_set(l->paths, sizeof(*l->paths), 0);
	if (!we_paths_new(l->paths, l->name))
		return (wx_false);
	wx_buffer_set(&l->texture_type, sizeof(t_level_texture), 0);
	if (!we_texture_type_new(&l->texture_type, l->paths))
		return (wx_false);
	return (wx_true);
}
