#include "we_editor.h"

t_bool	we_paths_new(t_path *p, t_c8 *level)
{
	if (!we_path_new3(&p[we_map], "data/maps/", level, "/map.txt")
		|| !we_path_new3(&p[we_wall_north], "data/maps/", level, "/north.xpm")
		|| !we_path_new3(&p[we_wall_east], "data/maps/", level, "/east.xpm")
		|| !we_path_new3(&p[we_wall_south], "data/maps/", level, "/south.xpm")
		|| !we_path_new3(&p[we_wall_west], "data/maps/", level, "/west.xpm")
		|| !we_path_new3(&p[we_floor], "data/maps/", level, "/floor.xpm")
		|| !we_path_new3(&p[we_sky], "data/maps/", level, "/sky.xpm")
		|| !we_path_new3(&p[we_door], "data/maps/", level, "/door.xpm"))
	{
		return (we_paths_del(p));
	}
	return (wx_true);
}
