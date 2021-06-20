#include "we_draw.h"

static void	zz_coord_set(t_p2 start, t_p2 increment,
				t_p2 *coord)
{
	if (start.x < 0)
		(*coord).x = increment.x
			* fabsf(start.x);
	if (start.y < 0)
		(*coord).y = increment.y
			* fabsf(start.y);
}

static void	zz_increment_set(t_p2 start, t_p2 end, t_p2 *increment,
				t_texture *t)
{
	(*increment).x = t->width / fabsf(end.x - start.x);
	(*increment).y = t->height / fabsf(end.y - start.y);
}

static void	zz_temp_set(t_f32 *temp_x, t_f32 *temp_x_tex,
				t_f32 start_x, t_f32 coord_x)
{
	*temp_x = start_x;
	*temp_x_tex = coord_x;
}

static void	zz_draw_row(t_texture_index *i, t_p2 *start, t_frame_buffer *fb,
				t_texture *t)
{
	t_u32	color;

	i->index = (t_u32)i->coord.x + (t_u32)i->coord.y * t->width;
	if (i->index < i->max_index)
	{
		wx_buffer_copy(&color, t->buffer + (i->index * 4),
			sizeof(color));
		wx_draw_pixel(*start, fb, color);
	}
	start->x++;
	i->coord.x += i->increment.x;
}

void	we_draw_rec_texture(t_p2 start, t_p2 end,
				t_frame_buffer *fb, t_texture *t)
{
	t_texture_index	i;
	t_f32			temp_x;
	t_f32			temp_x_tex;

	i.max_index = t->height * t->width;
	zz_increment_set(start, end, &i.increment, t);
	wx_buffer_set(&i.coord, sizeof(t_p2), 0);
	zz_coord_set(start, i.increment, &i.coord);
	we_draw_clip(&start, fb);
	we_draw_clip(&end, fb);
	zz_temp_set(&temp_x, &temp_x_tex, start.x, i.coord.x);
	while (start.y <= end.y)
	{
		start.x = temp_x;
		i.coord.x = temp_x_tex;
		while (start.x <= end.x)
			zz_draw_row(&i, &start, fb, t);
		start.y++;
		i.coord.y += i.increment.y;
	}
}
