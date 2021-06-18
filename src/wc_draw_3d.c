#include "wc_client.h"
#include "wc_draw.h"
#include "wx_draw.h"
#include "unistd.h"

static void	zz_draw_context_new(t_draw_context *dc, t_client *c, t_q4 const *o,
	t_p3 const *p)
{
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
	world_from_object = wx_m44_new_q4_p3(o, p);
	c->camera.orientation = c->player_orientation;
	c->camera.position = c->player_position;
	view_from_world = wx_m44_new_inverse_q4_p3(&c->camera.orientation,
			&c->camera.position);
	dc->view_from_object = wx_m44_mul_m44(&view_from_world, &world_from_object);
}

static void	zz_draw_map(t_client *c)
{
	t_draw_context	dc;
	t_q4			o;
	t_p3			p;

	o = (t_q4){0.0f, 0.0f, 0.0f, 1.0f};
	p = (t_p3){0.0f, 0.0f, 0.0f};
	zz_draw_context_new(&dc, c, &o, &p);
	wc_draw_mesh(&dc, &c->map_mesh.floor, &c->map.textures.floor);
	wc_draw_mesh(&dc, &c->map_mesh.north, &c->map.textures.walls[we_north]);
	wc_draw_mesh(&dc, &c->map_mesh.east, &c->map.textures.walls[we_east]);
	wc_draw_mesh(&dc, &c->map_mesh.west, &c->map.textures.walls[we_west]);
	wc_draw_mesh(&dc, &c->map_mesh.south, &c->map.textures.walls[we_south]);
}

static void	zz_draw_others(t_client *c)
{
	t_draw_context	dc;
	t_u64			i;

	i = 0;
	while (i < c->others_size)
	{
		zz_draw_context_new(&dc, c, c->other_orientations + i,
			c->other_positions + i);
		wc_draw_mesh(&dc, &c->test_mesh, &c->test_texture);
		++i;
	}
}

void	wc_draw_3d(t_client *c)
{
	wx_buffer_set(c->frame_buffer.data, c->frame_buffer.data_size, 0);
	wx_buffer_set(c->depth_buffer.data, c->depth_buffer.data_size, 0);
	zz_draw_map(c);
	zz_draw_others(c);
	wc_draw_copy(c, &c->frame_buffer);
}
