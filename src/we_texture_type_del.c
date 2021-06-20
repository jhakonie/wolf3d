#include "we_editor.h"

t_bool	we_textures_del(t_map_textures *textures)
{
	free(textures->walls[we_north].buffer);
	free(textures->walls[we_east].buffer);
	free(textures->walls[we_south].buffer);
	free(textures->walls[we_west].buffer);
	free(textures->skys[we_north].buffer);
	free(textures->skys[we_east].buffer);
	free(textures->skys[we_south].buffer);
	free(textures->skys[we_west].buffer);
	free(textures->floor.buffer);
	free(textures->door.buffer);
	return (wx_false);
}
