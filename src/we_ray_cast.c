/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_ray_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:25:44 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/23 00:59:42 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

static t_bool		zz_is_wall(t_item *chart, t_ray *ray,
						t_p2 intersection, t_u32 line)
{
	t_u32	block_y;
	t_u32	block_x;
	t_u32	block_count;
	t_u32	index;

	ray->end = intersection;
	block_count = WE_GRID_DIVIDE * WE_GRID_DIVIDE;
	block_y = intersection.y / WE_BLOCK_W;
	block_x = intersection.x / WE_BLOCK_W;
	index = block_x + block_y * WE_GRID_DIVIDE;
	if (block_x < 0 || block_x >= WE_GRID_DIVIDE ||
			block_y < 0 || block_y >= WE_GRID_DIVIDE)
		return (wx_false);
	if (ray->angle_d <= 180 && ray->angle_d >= 0 && line == WE_HORIZONTAL)
		index -= WE_GRID_DIVIDE;
	else if (ray->angle_d >= 90 && ray->angle_d <= 270 && line == WE_VERTICAL)
		index -= 1;
	if (index >= 0 && index < block_count - 1)
	{
		if ((we_ray_cast_check_map(chart, ray, line, index)))
			return (wx_true);
	}
	return (wx_false);
}

t_f32				zz_distance_to_wall(t_p2 start, t_p2 end)
{
	t_f32	distance;

	distance = sqrt(pow((end.x - start.x), 2.0) + pow((end.y - start.y), 2.0));
	return (distance);
}

static t_f32		zz_dist_horizontal_wall(t_ray *ray, t_item *chart)
{
	t_p2	intersection;
	t_u32	block_y;
	t_f32	world_end_x;

	world_end_x = WE_BLOCK_W * WE_GRID_DIVIDE;
	block_y = ray->start.y / WE_BLOCK_W;
	if (ray->angle_d >= 180 && ray->angle_d <= 360)
		block_y += 1;
	intersection.y = block_y * WE_BLOCK_W;
	while (block_y < WE_GRID_DIVIDE && block_y >= 0)
	{
		block_y = intersection.y / WE_BLOCK_W;
		intersection.x = (intersection.y - ray->b) / ray->k;
		if (intersection.x < 0 || intersection.x >= world_end_x ||
			(ray->angle_d == 180 || ray->angle_d == 0 || ray->angle_d == 360)
		|| block_y < 0 || block_y >= WE_GRID_DIVIDE)
			break ;
		if ((zz_is_wall(chart, ray, intersection, WE_HORIZONTAL)))
			return (zz_distance_to_wall(ray->start, intersection));
		if (ray->angle_d < 180 && ray->angle_d > 0)
			intersection.y -= WE_BLOCK_W;
		else
			intersection.y += WE_BLOCK_W;
	}
	return (0);
}

static t_f32		zz_dist_vertical_wall(t_ray *ray, t_item *chart)
{
	t_p2	intersection;
	t_u32	block_x;
	t_f32	world_end_y;

	world_end_y = WE_BLOCK_W * WE_GRID_DIVIDE;
	block_x = ray->start.x / WE_BLOCK_W;
	if (ray->angle_d <= 90 || ray->angle_d >= 270)
		block_x += 1;
	intersection.x = block_x * WE_BLOCK_W;
	while (block_x < WE_GRID_DIVIDE && block_x >= 0)
	{
		block_x = intersection.x / WE_BLOCK_W;
		intersection.y = ray->k * intersection.x + ray->b;
		if (intersection.y < 0 || intersection.y >= world_end_y ||
			(ray->angle_d == 90 || ray->angle_d == 270)
		|| block_x < 0 || block_x >= WE_GRID_DIVIDE)
			break ;
		if ((zz_is_wall(chart, ray, intersection, WE_VERTICAL)))
			return (zz_distance_to_wall(ray->start, intersection));
		if (ray->angle_d > 90 && ray->angle_d < 270)
			intersection.x -= WE_BLOCK_W;
		else
			intersection.x += WE_BLOCK_W;
	}
	return (0);
}

void				we_ray_cast(t_ray *ray, t_item *chart)
{
	t_f32	vertical;
	t_f32	horizontal;

	vertical = 0;
	horizontal = 0;
	horizontal = zz_dist_horizontal_wall(ray, chart);
	vertical = zz_dist_vertical_wall(ray, chart);
	horizontal *= cos(wx_to_radians(ray->angle_to_player_d));
	vertical *= cos(wx_to_radians(ray->angle_to_player_d));
	if (vertical < horizontal)
	{
		ray->dist_to_wall = vertical;
		if (vertical == 0)
			ray->dist_to_wall = horizontal;
	}
	else
	{
		ray->dist_to_wall = horizontal;
		if (horizontal == 0)
			ray->dist_to_wall = vertical;
	}
}
