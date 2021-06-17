#include "wc_client.h"
#include "wx_path.h"

static t_bool	zz_map_mesh(t_map_mesh *mm, char const *map_name)
{
	t_map	m;
	t_path	p;

	if (!wx_path_new3(&p, "data/maps/", map_name, "/map.txt"))
	{
		return (wx_false);
	}
	if (!wc_map_new_from_file(&m, p.buffer))
	{
		wx_path_del(&p);
		return (wx_false);
	}
	if (!wc_map_mesh_new_from_map(mm, &m))
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
	if (!zz_texture(&c->floor_texture, map_name, "/floor.xpm")
		|| !zz_texture(&c->north_texture, map_name, "/north.xpm")
		|| !zz_texture(&c->east_texture, map_name, "/east.xpm")
		|| !zz_texture(&c->west_texture, map_name, "/west.xpm")
		|| !zz_texture(&c->south_texture, map_name, "/south.xpm"))
	{
		return (wx_false);
	}
	return (wx_true);
}

t_bool	wc_client_load_data(t_client *c, char const *map_name)
{
	if (!zz_map_mesh(&c->map_mesh, map_name) || !zz_textures(c, map_name))
	{
		return (wx_false);
	}
	return (wx_true);
}
