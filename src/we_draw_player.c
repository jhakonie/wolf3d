/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:46:35 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/02 16:06:32 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static void	zz_draw_rays(t_frame_buffer *fb, t_editor *e, t_p2 start)
{
	t_f32	angle_d;
	t_ray	ray;
	t_p2	end;

	angle_d = 0;
	wx_buffer_set(&ray, sizeof(t_ray), 0);
	we_ray_init(&ray, e->player.fov_d, fb->width - 1, e->player.position);
	ray.tile_type_to_find = 1;
	while (ray.nb < fb->width - 1)
	{
		we_ray_calculate(&ray, angle_d, e->player.direction_d);
		we_ray_cast(&ray, e->map.tiles);
		end.x = (ray.tile.hit.x / WE_BLOCK_W) * e->map.grid.part.x
			+ e->tools.end.x;
		end.y = ray.tile.hit.y / WE_BLOCK_W * e->map.grid.part.y;
		if (ray.tile.side != we_no_wall)
			we_draw_line(start, end, fb, 0x00FF00);
		angle_d += ray.angle_increment_d;
		ray.nb++;
	}
}

static t_bool	zz_point_inside_map(t_p2 a,
					t_map *m)
{
	if (a.x < m->grid.start.x || a.y < m->grid.start.y
		|| a.x >= m->grid.end.x || a.y >= m->grid.end.y)
		return (wx_false);
	return (wx_true);
}

static t_bool	zz_inside_map(t_triangle *t,
					t_map *m)
{
	if (t->a.x < m->grid.start.x || t->b.x < m->grid.start.x
		|| t->c.x < m->grid.start.x || t->a.y < m->grid.start.y
		|| t->b.y < m->grid.start.y || t->c.y < m->grid.start.y)
		return (wx_false);
	if (t->a.x >= m->grid.end.x || t->b.x >= m->grid.end.x
		|| t->c.x >= m->grid.end.x || t->a.y >= m->grid.end.y
		|| t->b.y >= m->grid.end.y || t->c.y >= m->grid.end.y)
		return (wx_false);
	return (wx_true);
}

static void	zz_draw_triangle(t_editor *e, t_p2 base, t_p2 tip)
{
	t_triangle	t;
	t_p2		delta;
	t_p2		base_a;
	t_p2		base_b;

	delta.x = cosf((90 + e->player.direction_d) * WE_TO_RAD)
		* e->map.grid.part.x * 0.3f;
	delta.y = -(sinf((90 + e->player.direction_d) * WE_TO_RAD)
			* e->map.grid.part.y * 0.3f);
	base_a.x = base.x - delta.x;
	base_a.y = base.y - delta.y;
	base_b.x = base.x + delta.x;
	base_b.y = base.y + delta.y;
	we_init_triangle(base_a, base_b, tip, &t);
	if (zz_inside_map(&t, &e->map))
		we_draw_triangle(0xFF00D0, &t, &e->frame_buffer);
}

void	we_draw_player(t_editor *e)
{
	t_p2	player;
	t_p2	triangle_base;
	t_p2	triangle_tip;
	t_p2	delta;

	player.x = (e->player.position.x / WE_BLOCK_W) * e->map.grid.part.x
		+ e->tools.end.x;
	player.y = e->player.position.y / WE_BLOCK_W * e->map.grid.part.y;
	delta.x = (cosf(e->player.direction_d * WE_TO_RAD) * e->map.grid.part.x);
	delta.y = -(sinf(e->player.direction_d * WE_TO_RAD) * e->map.grid.part.y);
	triangle_base.x = (player.x - 0.5f * delta.x);
	triangle_base.y = (player.y - 0.5f * delta.y);
	triangle_tip.x = (player.x + delta.x);
	triangle_tip.y = (player.y + delta.y);
	if (player.x > e->tools.end.x)
		zz_draw_triangle(e, triangle_base, triangle_tip);
	if (e->map.draw_rays)
		zz_draw_rays(&e->frame_buffer, e, player);
	if (zz_point_inside_map(player, &e->map))
		we_draw_pixel(player, &e->frame_buffer, 0xFFFF00);
}
