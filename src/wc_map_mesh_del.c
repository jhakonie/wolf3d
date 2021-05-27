#include "wc_draw.h"

void	wc_map_mesh_del(t_map_mesh *mm)
{
	wc_mesh_del(&mm->floor);
	wc_mesh_del(&mm->north);
	wc_mesh_del(&mm->east);
	wc_mesh_del(&mm->west);
	wc_mesh_del(&mm->south);
}
