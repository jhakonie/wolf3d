/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_ray_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:25:44 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/29 00:19:49 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

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
	if (index < block_count - 1)
	{
		ray->wall.chart_index = index;
		if (chart[index].id == 1 || chart[index].id == 2)
			return (wx_true);
	}
	return (wx_false);
}

static t_found	zz_wall_values(t_ray *ray, t_item *chart, t_side side)
{
	if (side == we_no_wall)
	{
		wx_buffer_set(&ray->wall, sizeof(ray->wall), 0);
		return (ray->wall);
	}
	ray->wall.side = side;
	ray->wall.chart_id = chart[ray->wall.chart_index].id;
	ray->wall.distance = sqrt(pow((ray->wall.end.x - ray->start.x), 2.0)
			+ pow((ray->wall.end.y - ray->start.y), 2.0));
	ray->wall.compass = we_wall_compass_direction(ray->angle_d, side);
	return (ray->wall);
}

static t_found	zz_dist_horizontal_wall(t_ray *ray, t_item *chart)
{
	t_p2	intersection_w;
	t_u32	block_y;
	t_f32	world_end_x;

	world_end_x = WE_BLOCK_W * WE_GRID_DIVIDE;
	block_y = ray->start.y / WE_BLOCK_W;
	if (ray->angle_d >= 180 && ray->angle_d <= 360)
		block_y += 1;
	intersection_w.y = block_y * WE_BLOCK_W;
	while (block_y < WE_GRID_DIVIDE)
	{
		block_y = intersection_w.y / WE_BLOCK_W;
		intersection_w.x = (intersection_w.y - ray->b) / ray->k;
		if (intersection_w.x < 0 || intersection_w.x >= world_end_x
			|| (ray->angle_d == 180 || ray->angle_d == 0 || ray->angle_d == 360)
			|| block_y >= WE_GRID_DIVIDE)
			break ;
		if ((zz_is_wall(chart, ray, intersection_w, we_horisontal)))
			return (zz_wall_values(ray, chart, we_horisontal));
		if (ray->angle_d < 180 && ray->angle_d > 0)
			intersection_w.y -= WE_BLOCK_W;
		else
			intersection_w.y += WE_BLOCK_W;
	}
	return (zz_wall_values(ray, chart, we_no_wall));
}

static t_found	zz_dist_vertical_wall(t_ray *ray, t_item *chart)
{
	t_p2	intersection_w;
	t_u32	block_x;
	t_f32	world_end_y;

	world_end_y = WE_BLOCK_W * WE_GRID_DIVIDE;
	block_x = ray->start.x / WE_BLOCK_W;
	if (ray->angle_d <= 90 || ray->angle_d >= 270)
		block_x += 1;
	intersection_w.x = block_x * WE_BLOCK_W;
	while (block_x < WE_GRID_DIVIDE)
	{
		block_x = intersection_w.x / WE_BLOCK_W;
		intersection_w.y = ray->k * intersection_w.x + ray->b;
		if (intersection_w.y < 0 || intersection_w.y >= world_end_y
			|| (ray->angle_d == 90 || ray->angle_d == 270)
			|| block_x >= WE_GRID_DIVIDE)
			break ;
		if ((zz_is_wall(chart, ray, intersection_w, we_vertical)))
			return (zz_wall_values(ray, chart, we_vertical));
		if (ray->angle_d > 90 && ray->angle_d < 270)
			intersection_w.x -= WE_BLOCK_W;
		else
			intersection_w.x += WE_BLOCK_W;
	}
	return (zz_wall_values(ray, chart, we_no_wall));
}

void	we_ray_cast(t_ray *ray, t_item *chart)
{
	t_found	vertical;
	t_found	horizontal;

	horizontal = zz_dist_horizontal_wall(ray, chart);
	vertical = zz_dist_vertical_wall(ray, chart);
	vertical.distance *= cos(wx_to_radians(ray->angle_to_player_d));
	horizontal.distance *= cos(wx_to_radians(ray->angle_to_player_d));
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
