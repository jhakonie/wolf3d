/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:46:35 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/19 00:35:23 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static void	zz_raycast_door(t_ray *ray, t_map *m, t_p2 *end, t_map_view *mv)
{
	ray->tile_type_to_find = 2;
	we_ray_cast(ray, m->tiles);
	(*end).x = (ray->tile.hit.x / WX_TILE_WIDTH) * mv->grid.part.x
		+ mv->grid.start.x;
	(*end).y = ray->tile.hit.y / WX_TILE_WIDTH * mv->grid.part.y;
}

/*
** Raycast walls and doors separately and draw a line to them.
*/

static void	zz_draw_rays(t_frame_buffer *fb, t_editor *e, t_p2 start)
{
	t_f32	angle_d;
	t_ray	ray;
	t_p2	end;

	angle_d = 0;
	wx_buffer_set(&ray, sizeof(t_ray), 0);
	we_ray_init(&ray, e->player.fov_d, fb->width - 1, e->player.position);
	while (ray.nb < fb->width - 1)
	{
		ray.tile_type_to_find = 1;
		we_ray_calculate(&ray, angle_d, e->player.direction_d);
		we_ray_cast(&ray, e->level.map.tiles);
		end.x = (ray.tile.hit.x / WX_TILE_WIDTH) * e->map_view.grid.part.x
			+ e->tools.end.x;
		end.y = ray.tile.hit.y / WX_TILE_WIDTH * e->map_view.grid.part.y;
		if (ray.tile.side != we_no_wall)
			we_draw_line(start, end, fb, 0x00FF00);
		zz_raycast_door(&ray, &e->level.map, &end, &e->map_view);
		if (ray.tile.side != we_no_wall && ray.tile.tiles_id == 2)
			we_draw_line(start, end, fb, 0xaa00ff);
		angle_d += ray.angle_increment_d;
		ray.nb++;
	}
}

static t_bool	zz_inside_map(t_triangle *t,
					t_map_view *m)
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

/*
** Set triangle tips around player.
*/

static void	zz_draw_triangle(t_editor *e, t_p2 base, t_p2 tip)
{
	t_triangle	t;
	t_p2		delta;
	t_p2		base_a;
	t_p2		base_b;

	delta.x = cosf((wx_to_radians(90 + e->player.direction_d)))
		* e->map_view.grid.part.x * 0.3f;
	delta.y = -(sinf((wx_to_radians(90 + e->player.direction_d)))
			* e->map_view.grid.part.y * 0.3f);
	base_a.x = base.x - delta.x;
	base_a.y = base.y - delta.y;
	base_b.x = base.x + delta.x;
	base_b.y = base.y + delta.y;
	we_init_triangle(base_a, base_b, tip, &t);
	if (zz_inside_map(&t, &e->map_view))
		we_draw_triangle(0xFF00D0, &t, &e->frame_buffer);
}

/*
** Draw a triangle around the player location.
** Draw one pixel at player location.
** Draw rays.
*/

void	we_draw_player(t_editor *e)
{
	t_p2	player;
	t_p2	triangle_base;
	t_p2	triangle_tip;
	t_p2	delta;

	player.x = (e->player.position.x / WX_TILE_WIDTH) * e->map_view.grid.part.x
		+ e->tools.end.x;
	player.y = e->player.position.y / WX_TILE_WIDTH * e->map_view.grid.part.y;
	delta.x = (cosf(wx_to_radians(e->player.direction_d))
			* e->map_view.grid.part.x);
	delta.y = -(sinf(wx_to_radians(e->player.direction_d))
			* e->map_view.grid.part.y);
	triangle_base.x = (player.x - 0.5f * delta.x);
	triangle_base.y = (player.y - 0.5f * delta.y);
	triangle_tip.x = (player.x + delta.x);
	triangle_tip.y = (player.y + delta.y);
	if (player.x > e->tools.end.x)
		zz_draw_triangle(e, triangle_base, triangle_tip);
	if (e->map_view.draw_rays)
		zz_draw_rays(&e->frame_buffer, e, player);
	if (player.x > e->map_view.grid.start.x
		&& player.y > e->map_view.grid.start.y
		&& player.x < e->map_view.grid.end.x
		&& player.y < e->map_view.grid.end.y)
		we_draw_pixel(player, &e->frame_buffer, 0xFFFF00);
}
