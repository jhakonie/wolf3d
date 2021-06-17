#include "we_editor.h"

t_bool	we_paths_new(t_path *p, t_c8 *level)
{
	if (!wx_path_new3(&p[we_map], "data/maps/", level, "/map.txt")
		|| !wx_path_new3(&p[we_wall_north], "data/maps/", level, "/north.xpm")
		|| !wx_path_new3(&p[we_wall_east], "data/maps/", level, "/east.xpm")
		|| !wx_path_new3(&p[we_wall_south], "data/maps/", level, "/south.xpm")
		|| !wx_path_new3(&p[we_wall_west], "data/maps/", level, "/west.xpm")
		|| !wx_path_new3(&p[we_floor], "data/maps/", level, "/floor.xpm")
		|| !wx_path_new3(&p[we_sky], "data/maps/", level, "/sky.xpm")
		|| !wx_path_new3(&p[we_door], "data/maps/", level, "/door.xpm"))
	{
		return (we_paths_del(p, WE_RESOURCES_COUNT));
	}
	return (wx_true);
}
