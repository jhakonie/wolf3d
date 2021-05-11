#include "stdlib.h"

#include "wc_draw.h"

void	wc_pipeline_buffers_del(t_pipeline_buffers *pb)
{
	free(pb->visible_indices);
	free(pb->view_positions);
	free(pb->uvs);
	free(pb->screen_positions);
}
