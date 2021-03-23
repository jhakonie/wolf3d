/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_ray_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:25:44 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/23 20:52:53 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

static t_bool		zz_is_wall(t_item *chart, t_ray *ray,
						t_p2 intersection, t_side line)
{
	t_u32	block_y;
	t_u32	block_x;
	t_u32	block_count;
	t_u32	index;

	ray->wall.end = intersection;
	block_count = WE_GRID_DIVIDE * WE_GRID_DIVIDE;
	block_y = intersection.y / WE_BLOCK_W;
	block_x = intersection.x / WE_BLOCK_W;
	index = block_x + block_y * WE_GRID_DIVIDE;
	if (block_x >= WE_GRID_DIVIDE || block_y >= WE_GRID_DIVIDE)
		return (wx_false);
	if (ray->angle_d <= 180 && ray->angle_d >= 0 && line == we_horisontal)
		index -= WE_GRID_DIVIDE;
	else if (ray->angle_d >= 90 && ray->angle_d <= 270 && line == we_vertical)
		index -= 1;
	if (index < block_count - 1)
	{
		if (chart[index].id == 1 || chart[index].id == 2)
		{
			ray->wall.chart_index = index;
			return (wx_true);
		}
	}
	return (wx_false);
}

static t_found		zz_wall_values(t_ray *ray, t_item *chart, t_side side)
{
	if (side == we_no_wall)
	{
		wx_buffer_set(&ray->wall, sizeof(ray->wall), 0);
		return (ray->wall);
	}
	ray->wall.side = side;
	ray->wall.chart_id = chart[ray->wall.chart_index].id;
	ray->wall.distance =
			sqrt(pow((ray->wall.end.x - ray->start.x), 2.0) +
			pow((ray->wall.end.y - ray->start.y), 2.0));
	if (side == we_horisontal)
	{
		if (ray->angle_d > 180)
			ray->wall.compass = we_south;
		else
			ray->wall.compass = we_north;
	}
	else
	{
		if (ray->angle_d > 90 && ray->angle_d < 270)
			ray->wall.compass = we_west;
		else
			ray->wall.compass = we_east;
	}
	return (ray->wall);
}

static t_found		zz_dist_horizontal_wall(t_ray *ray, t_item *chart)
{
	t_p2	intersection;
	t_u32	block_y;
	t_f32	world_end_x;

	world_end_x = WE_BLOCK_W * WE_GRID_DIVIDE;
	block_y = ray->start.y / WE_BLOCK_W;
	if (ray->angle_d >= 180 && ray->angle_d <= 360)
		block_y += 1;
	intersection.y = block_y * WE_BLOCK_W;
	while (block_y < WE_GRID_DIVIDE)
	{
		block_y = intersection.y / WE_BLOCK_W;
		intersection.x = (intersection.y - ray->b) / ray->k;
		if (intersection.x < 0 || intersection.x >= world_end_x ||
			(ray->angle_d == 180 || ray->angle_d == 0 || ray->angle_d == 360) ||
			block_y >= WE_GRID_DIVIDE)
			break ;
		if ((zz_is_wall(chart, ray, intersection, we_horisontal)))
			return (zz_wall_values(ray, chart, we_horisontal));
		if (ray->angle_d < 180 && ray->angle_d > 0)
			intersection.y -= WE_BLOCK_W;
		else
			intersection.y += WE_BLOCK_W;
	}
	return (zz_wall_values(ray, chart, we_no_wall));
}

static t_found		zz_dist_vertical_wall(t_ray *ray, t_item *chart)
{
	t_p2	intersection;
	t_u32	block_x;
	t_f32	world_end_y;

	world_end_y = WE_BLOCK_W * WE_GRID_DIVIDE;
	block_x = ray->start.x / WE_BLOCK_W;
	if (ray->angle_d <= 90 || ray->angle_d >= 270)
		block_x += 1;
	intersection.x = block_x * WE_BLOCK_W;
	while (block_x < WE_GRID_DIVIDE)
	{
		block_x = intersection.x / WE_BLOCK_W;
		intersection.y = ray->k * intersection.x + ray->b;
		if (intersection.y < 0 || intersection.y >= world_end_y ||
			(ray->angle_d == 90 || ray->angle_d == 270) ||
			block_x >= WE_GRID_DIVIDE)
			break ;
		if ((zz_is_wall(chart, ray, intersection, we_vertical)))
			return (zz_wall_values(ray, chart, we_vertical));
		if (ray->angle_d > 90 && ray->angle_d < 270)
			intersection.x -= WE_BLOCK_W;
		else
			intersection.x += WE_BLOCK_W;
	}
	return (zz_wall_values(ray, chart, we_no_wall));
}

void				we_ray_cast(t_ray *ray, t_item *chart)
{
	t_found	vertical;
	t_found	horizontal;

	horizontal = zz_dist_horizontal_wall(ray, chart);
	vertical = zz_dist_vertical_wall(ray, chart);
	horizontal.distance *= cos(wx_to_radians(ray->angle_to_player_d));
	vertical.distance *= cos(wx_to_radians(ray->angle_to_player_d));
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
