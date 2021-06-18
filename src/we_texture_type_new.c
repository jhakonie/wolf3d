#include "we_editor.h"

static t_bool	zz_wall_texture(t_map_textures *textures, t_path *paths)
{
	if (!we_texture_new(paths[we_wall_north].buffer,
			&textures->walls[we_north]))
		return (we_textures_del(textures));
	write(1, "\nwall north texture 1/4 loaded\n", 32);
	if (!we_texture_new(paths[we_wall_east].buffer,
			&textures->walls[we_east]))
		return (we_textures_del(textures));
	write(1, "\nwall east texture 2/4 loaded\n", 31);
	if (!we_texture_new(paths[we_wall_south].buffer,
			&textures->walls[we_south]))
		return (we_textures_del(textures));
	write(1, "\nwall south texture 3/4 loaded\n", 32);
	if (!we_texture_new(paths[we_wall_west].buffer,
			&textures->walls[we_west]))
		return (we_textures_del(textures));
	write(1, "\nwall west texture 4/4 loaded\n", 31);
	return (wx_true);
}

t_bool	we_textures_new(t_map_textures *textures, t_path *paths)
{
	if (!zz_wall_texture(textures, paths))
		return (wx_false);
	if (!we_texture_new(paths[we_floor].buffer, &textures->floor))
		return (we_textures_del(textures));
	write(1, "\nfloor texture loaded\n", 23);
	if (!we_texture_new(paths[we_sky].buffer, &textures->sky))
		return (we_textures_del(textures));
	write(1, "\nsky texture loaded\n", 21);
	if (!we_texture_new(paths[we_door].buffer, &textures->door))
		return (we_textures_del(textures));
	write(1, "\ndoor texture loaded\n", 22);
	return (wx_true);
}
