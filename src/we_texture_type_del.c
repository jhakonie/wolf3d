#include "we_editor.h"

t_bool	we_texture_type_del(t_level_texture *texture_type)
{
	free(texture_type->wall[we_north].texture);
	free(texture_type->wall[we_east].texture);
	free(texture_type->wall[we_south].texture);
	free(texture_type->wall[we_west].texture);
	free(texture_type->floor.texture);
	free(texture_type->sky.texture);
	free(texture_type->door.texture);
	return (wx_false);
}
