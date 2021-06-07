#include "we_editor.h"

void	we_level_del(t_level *l)
{
	we_path_del(l->paths);
	we_texture_type_del(&l->texture_type);
	l->name = WX_NULL;
}
