#include "wc_client.h"
#include "wx_path.h"
#include "wx_draw.h"

static t_bool	zz_map_mesh(t_map_mesh *mm, char const *map_name, t_map *map)
{
	t_path	p;

	if (!wx_path_new3(&p, "data/maps/", map_name, "/map.txt"))
	{
		return (wx_false);
	}
	if (!wc_map_new_from_file(map, p.buffer))
	{
		wx_path_del(&p);
		return (wx_false);
	}
	if (!wc_map_mesh_new_from_map(mm, map))
	{
		wx_path_del(&p);
		return (wx_false);
	}
	wx_path_del(&p);
	return (wx_true);
}

static t_bool	zz_texture(t_texture *t, char const *map_name,
	char const *filename)
{
	t_path	p;

	if (!wx_path_new3(&p, "data/maps/", map_name, filename))
	{
		return (wx_false);
	}
	if (!wc_texture_new_from_file(t, p.buffer))
	{
		wx_path_del(&p);
		if (!wx_path_new3(&p, "data/maps/", "default", filename))
		{
			return (wx_false);
		}
		if (!wc_texture_new_from_file(t, p.buffer))
		{
			wx_path_del(&p);
			return (wx_false);
		}
	}
	wx_path_del(&p);
	return (wx_true);
}

static t_bool	zz_textures(t_client *c, char const *map_name)
{
	if (!zz_texture(&c->map.textures.floor, map_name, "/floor.xpm")
		|| !zz_texture(&c->map.textures.sky, map_name, "/sky.xpm")
		|| !zz_texture(&c->map.textures.door, map_name, "/door.xpm")
		|| !zz_texture(&c->map.textures.walls[we_north], map_name, "/north.xpm")
		|| !zz_texture(&c->map.textures.walls[we_east], map_name, "/east.xpm")
		|| !zz_texture(&c->map.textures.walls[we_west], map_name, "/west.xpm")
		|| !zz_texture(&c->map.textures.walls[we_south],
			map_name, "/south.xpm"))
	{
		return (wx_false);
	}
	return (wx_true);
}

t_bool	wc_client_load_data(t_client *c, char const *map_name)
{
	if (!zz_map_mesh(&c->map_mesh, map_name, &c->map)
		|| !zz_textures(c, map_name))
	{
		return (wx_false);
	}
	return (wx_true);
}
