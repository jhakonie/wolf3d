#include "wc_client.h"
#include "wc_draw.h"

static void	zz_draw_context_new(t_draw_context *dc, t_client *c)
{
	t_q4	object_orientation;
	t_p3	object_position;
	t_m44	view_from_world;
	t_m44	world_from_object;

	dc->buffers = &c->pipeline_buffers;
	dc->buffers->screen_positions_size = 0;
	dc->buffers->view_positions_size = 0;
	dc->buffers->visible_indices_size = 0;
	dc->frame_buffer = &c->frame_buffer;
	dc->depth_buffer = &c->depth_buffer;
	dc->clip_from_view = wx_m44_new_perspective(c->camera.hfov_rad,
			c->camera.aspect_ratio, c->camera.near, c->camera.far);
	dc->frustum = wx_frustum_new(&dc->clip_from_view);
	object_orientation = (t_q4){0.0f, 0.0f, 0.0f, 1.0f};
	object_position = (t_p3){0.0f, 0.0f, 0.0f};
	world_from_object = wx_m44_new_q4_p3(&object_orientation, &object_position);
	c->camera.orientation = c->player_orientation;
	c->camera.position = c->player_position;
	view_from_world = wx_m44_new_inverse_q4_p3(&c->camera.orientation,
			&c->camera.position);
	dc->view_from_object = wx_m44_mul_m44(&view_from_world, &world_from_object);
}

void	wc_draw_3d(t_client *c)
{
	t_draw_context	dc;

	zz_draw_context_new(&dc, c);
	wc_draw_clear(&dc);
	wc_draw_mesh(&dc, &c->test_mesh, &c->test_texture);
	wc_draw_mesh(&dc, &c->map_mesh.floor, &c->floor_texture);
	wc_draw_mesh(&dc, &c->map_mesh.north, &c->north_texture);
	wc_draw_mesh(&dc, &c->map_mesh.east, &c->east_texture);
	wc_draw_mesh(&dc, &c->map_mesh.west, &c->west_texture);
	wc_draw_mesh(&dc, &c->map_mesh.south, &c->south_texture);
	wc_draw_copy(c, dc.frame_buffer);
}
