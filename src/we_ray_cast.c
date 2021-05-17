/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_ray_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:25:44 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/16 13:49:01 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

/*
** Calculate distance to wall and wall projected height.
** Define wall type, side and wall compass direction.
*/

static t_found	zz_wall_values(t_ray *ray, t_item *chart, t_side side)
{
	if (side == we_no_wall)
	{
		wx_buffer_set(&ray->wall, sizeof(ray->wall), 0);
		return (ray->wall);
	}
	ray->wall.side = side;
	ray->wall.chart_id = chart[ray->wall.chart_index].id;
	ray->wall.distance = sqrtf(powf((ray->wall.end.x - ray->start.x), 2.0)
			+ powf((ray->wall.end.y - ray->start.y), 2.0));
	ray->wall.distance *= cosf(wx_to_radians(ray->angle_to_player_d));
	ray->wall.projected_height = (ray->dist_to_screen / ray->wall.distance)
		* WE_BLOCK_W;
	ray->wall.compass = we_wall_compass_direction(ray->angle_d, side);
	return (ray->wall);
}

/*
** Check if ray hit a wall. Save intersection point, chart index and
** ray values.
*/

/* todo: make this return ray.wall
** and set it to no_wall if index was out of bounds,
** otherwise outside map floor will be drawn based on prev. ray info
*/

static t_bool	zz_is_wall(t_item *chart, t_ray *ray, t_p2 intersection_w,
	t_side line)
{
	t_u32	block_y;
	t_u32	block_x;
	t_u32	block_count;
	t_u32	index;

	ray->wall.end = intersection_w;
	block_count = WE_GRID_DIVIDE * WE_GRID_DIVIDE;
	block_y = intersection_w.y / WE_BLOCK_W;
	block_x = intersection_w.x / WE_BLOCK_W;
	index = block_x + block_y * WE_GRID_DIVIDE;
	if (block_x >= WE_GRID_DIVIDE || block_y >= WE_GRID_DIVIDE
		|| (block_x == 0 && line == we_vertical))
		return (wx_false);
	if (ray->angle_d <= 180 && ray->angle_d >= 0 && line == we_horisontal)
		index -= WE_GRID_DIVIDE;
	else if (ray->angle_d >= 90 && ray->angle_d <= 270 && line == we_vertical)
		index -= 1;
	if (index < block_count)
	{
		ray->wall.chart_index = index;
		ray->wall = zz_wall_values(ray, chart, line);
		return (wx_true);
	}
	return (wx_false);
}

/*
** Find distance to horizontal wall, draw floor, update ray values.
*/

static t_found	zz_dist_horizontal_wall(t_ray *ray, t_item *chart,
					t_frame_buffer *fb, t_bool draw_3d)
{
	t_p2	intersection_w;
	t_u32	block_y;
	t_f32	world_end;

	world_end = WE_BLOCK_W * WE_GRID_DIVIDE;
	block_y = ray->start.y / WE_BLOCK_W;
	if (ray->angle_d >= 180 && ray->angle_d <= 360)
		block_y += 1;
	intersection_w.y = block_y * WE_BLOCK_W;
	while (intersection_w.y < world_end && intersection_w.y >= 0)
	{
		intersection_w.x = (intersection_w.y - ray->b) / ray->k;
		if (intersection_w.x < 0 || intersection_w.x >= world_end
			|| (ray->angle_d == 180 || ray->angle_d == 0 || ray->angle_d == 360)
			|| block_y >= WE_GRID_DIVIDE)
			break ;
		if ((zz_is_wall(chart, ray, intersection_w, we_horisontal)))
			we_draw_floor(*ray, fb, draw_3d);
		if (ray->wall.chart_id == 1 || ray->wall.chart_id == 2)
			return (ray->wall);
		intersection_w.y += WE_BLOCK_W;
		if (ray->angle_d < 180 && ray->angle_d > 0)
			intersection_w.y -= 2 * WE_BLOCK_W;
	}
	return (zz_wall_values(ray, chart, we_no_wall));
}

/*
** Find distance to vertical wall, draw floor, update ray values.
*/

static t_found	zz_dist_vertical_wall(t_ray *ray, t_item *chart,
					t_frame_buffer *fb, t_bool draw_3d)
{
	t_p2	intersection_w;
	t_u32	block_x;
	t_f32	world_end;

	world_end = WE_BLOCK_W * WE_GRID_DIVIDE;
	block_x = ray->start.x / WE_BLOCK_W;
	if (ray->angle_d <= 90 || ray->angle_d >= 270)
		block_x += 1;
	intersection_w.x = block_x * WE_BLOCK_W;
	while (intersection_w.x < world_end && intersection_w.x >= 0)
	{
		intersection_w.y = ray->k * intersection_w.x + ray->b;
		if (intersection_w.y < 0 || intersection_w.y >= world_end
			|| (ray->angle_d == 90 || ray->angle_d == 270)
			|| block_x >= WE_GRID_DIVIDE)
			break ;
		if ((zz_is_wall(chart, ray, intersection_w, we_vertical)))
			we_draw_floor(*ray, fb, draw_3d);
		if (ray->wall.chart_id == 1 || ray->wall.chart_id == 2)
			return (ray->wall);
		intersection_w.x += WE_BLOCK_W;
		if (ray->angle_d > 90 && ray->angle_d < 270)
			intersection_w.x -= 2 * WE_BLOCK_W;
	}
	return (zz_wall_values(ray, chart, we_no_wall));
}

/*
** Find the closest intersection point with horisontal and vertical
** walls. Choose the closer one to be drawn.
*/

void	we_ray_cast(t_ray *ray, t_item *chart, t_frame_buffer *fb,
			t_bool draw_3d)
{
	t_found	vertical;
	t_found	horizontal;

	horizontal = zz_dist_horizontal_wall(ray, chart, fb, draw_3d);
	vertical = zz_dist_vertical_wall(ray, chart, fb, draw_3d);
	if (vertical.distance < horizontal.distance)
	{
		ray->wall = vertical;
		if (vertical.distance == 0)
			ray->wall = horizontal;
	}
	else
	{
		ray->wall = horizontal;
		if (horizontal.distance == 0)
			ray->wall = vertical;
	}
}
