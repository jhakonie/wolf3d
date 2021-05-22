#include "wc_draw.h"

/*
** 2021-05-18 note: doing the error handling using wx_buffer_set() and then
** wc_map_mesh_del() on any error relies heavily on the types of subobjects
** map_mesh contains. the requirement is that all of them can be zeroed-out and
** calling the corresponding del function on the zeroed-out subobject is ok.
** what could possibly go wrong?
**
** 2021-05-21 note: north corresponds to +z axis, west corresponds to +x axis of
** a right handed y-up coordinate system:
**
**      y
**      ^
**      |
**      |
** -----+---->x west
**     /|
**    / |
**   z  |
** north
**
** and the map is on the xz-plane
*/
t_bool	wc_map_mesh_new_from_map(t_map_mesh *mm, t_map const *m)
{
	wx_buffer_set(mm, sizeof(*mm), 0);
	if (!wc_map_mesh_new_from_map_floor(mm, m)
		|| !wc_map_mesh_new_from_map_north(mm, m)
		|| !wc_map_mesh_new_from_map_east(mm, m)
		|| !wc_map_mesh_new_from_map_west(mm, m)
		|| !wc_map_mesh_new_from_map_south(mm, m))
	{
		wc_map_mesh_del(mm);
		return (wx_false);
	}
	return (wx_true);
}
