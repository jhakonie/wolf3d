#include "we_editor.h"

static t_bool	zz_wall_texture(t_level_texture *texture_type, t_path *paths)
{
	if (!we_texture_new(paths[we_wall_north].buffer,
			&texture_type->wall[we_north]))
		return (we_texture_type_del(texture_type));
	write(1, "\nwall north texture 1/4 loaded\n", 32);
	if (!we_texture_new(paths[we_wall_east].buffer,
			&texture_type->wall[we_east]))
		return (we_texture_type_del(texture_type));
	write(1, "\nwall east texture 2/4 loaded\n", 31);
	if (!we_texture_new(paths[we_wall_south].buffer,
			&texture_type->wall[we_south]))
		return (we_texture_type_del(texture_type));
	write(1, "\nwall south texture 3/4 loaded\n", 32);
	if (!we_texture_new(paths[we_wall_west].buffer,
			&texture_type->wall[we_west]))
		return (we_texture_type_del(texture_type));
	write(1, "\nwall west texture 4/4 loaded\n", 31);
	return (wx_true);
}

t_bool	we_texture_type_new(t_level_texture *texture_type, t_path *paths)
{
	if (!zz_wall_texture(texture_type, paths))
		return (wx_false);
	if (!we_texture_new(paths[we_floor].buffer, &texture_type->floor))
		return (we_texture_type_del(texture_type));
	write(1, "\nfloor texture loaded\n", 23);
	if (!we_texture_new(paths[we_sky].buffer, &texture_type->sky))
		return (we_texture_type_del(texture_type));
	write(1, "\nsky texture loaded\n", 21);
	if (!we_texture_new(paths[we_door].buffer, &texture_type->door))
		return (we_texture_type_del(texture_type));
	write(1, "\ndoor texture loaded\n", 22);
	return (wx_true);
}
