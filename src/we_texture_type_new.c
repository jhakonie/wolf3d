#include "we_editor.h"

static t_bool	zz_wall_texture(t_map_textures *textures, t_path *paths)
{
	if (!we_texture_new(paths[we_wall_north].buffer,
			&textures->walls[we_north]))
		return (we_textures_del(textures));
	if (!we_texture_new(paths[we_wall_east].buffer,
			&textures->walls[we_east]))
		return (we_textures_del(textures));
	if (!we_texture_new(paths[we_wall_south].buffer,
			&textures->walls[we_south]))
		return (we_textures_del(textures));
	if (!we_texture_new(paths[we_wall_west].buffer,
			&textures->walls[we_west]))
		return (we_textures_del(textures));
	return (wx_true);
}

t_bool	we_textures_new(t_map_textures *textures, t_path *paths)
{
	if (!zz_wall_texture(textures, paths))
		return (wx_false);
	if (!we_texture_new(paths[we_floor].buffer, &textures->floor))
		return (we_textures_del(textures));
	if (!we_texture_new(paths[we_sky_north].buffer, &textures->skys[we_north]))
		return (we_textures_del(textures));
	if (!we_texture_new(paths[we_sky_east].buffer, &textures->skys[we_east]))
		return (we_textures_del(textures));
	if (!we_texture_new(paths[we_sky_south].buffer, &textures->skys[we_south]))
		return (we_textures_del(textures));
	if (!we_texture_new(paths[we_sky_west].buffer, &textures->skys[we_west]))
		return (we_textures_del(textures));
	if (!we_texture_new(paths[we_door].buffer, &textures->door))
		return (we_textures_del(textures));
	return (wx_true);
}
