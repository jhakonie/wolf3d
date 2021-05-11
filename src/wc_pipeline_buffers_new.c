#include "wc_client.h"
#include "wc_draw.h"

static t_bool	zz_on_error(t_pipeline_buffers *pb, t_u8 i)
{
	if (i > 3)
		free(pb->visible_indices);
	if (i > 2)
		free(pb->view_positions);
	if (i > 1)
		free(pb->uvs);
	if (i > 0)
		free(pb->screen_positions);
	return (wx_false);
}

t_bool	wc_pipeline_buffers_new(t_pipeline_buffers *pb)
{
	pb->screen_positions
		= (t_p3 *)malloc(WC_PIPELINE_VERTICES_SIZE
			* sizeof(t_p3));
	if (!pb->screen_positions)
		return (zz_on_error(pb, 0));
	pb->screen_positions_size = 0;
	pb->uvs
		= (t_p2 *)malloc(WC_PIPELINE_VERTICES_SIZE * sizeof(t_p2));
	if (!pb->uvs)
		return (zz_on_error(pb, 1));
	pb->uvs_size = 0;
	pb->view_positions
		= (t_p3 *)malloc(WC_PIPELINE_VERTICES_SIZE * sizeof(t_p3));
	if (!pb->view_positions)
		return (zz_on_error(pb, 2));
	pb->view_positions_size = 0;
	pb->visible_indices
		= (t_u16 *)malloc(WC_PIPELINE_VERTICES_SIZE * sizeof(t_u16));
	if (!pb->visible_indices)
		return (zz_on_error(pb, 3));
	pb->visible_indices_size = 0;
	return (wx_true);
}
