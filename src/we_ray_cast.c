/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_ray_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:25:44 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/09 15:19:46 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

/*
** Calculate distance to wall and wall projected height.
** Define wall type, side and wall compass direction.
*/

static t_hit	zz_tile_values(t_ray *ray, t_map_tile *tiles, t_side side)
{
	t_p2	delta;

	if (side == we_no_wall)
	{
		wx_buffer_set(&ray->tile, sizeof(t_hit), 0);
		return (ray->tile);
	}
	ray->tile.side = side;
	ray->tile.tiles_id = tiles[ray->tile.tiles_index].id;
	delta.x = ray->tile.hit.x - ray->start.x;
	delta.y = ray->tile.hit.y - ray->start.y;
	ray->tile.distance = sqrtf(delta.x * delta.x + delta.y * delta.y);
	ray->tile.distance *= cosf(wx_to_radians(ray->angle_to_player_d));
	ray->tile.projected_height = (ray->dist_to_screen_w / ray->tile.distance)
		* WE_BLOCK_W;
	ray->tile.compass = we_wall_compass_direction(ray->angle_d, side);
	return (ray->tile);
}

/* 
** Check if the ray and vertical or horisontal map line intersection point
** hit a wall. Updates tile values.
*/

static t_bool	zz_is_wall(t_map_tile *tiles, t_ray *ray, t_p2 intersection_w,
	t_side line)
{
	t_u32			block_y;
	t_u32			block_x;
	static t_u32	block_count = WE_GRID_DIVIDE * WE_GRID_DIVIDE;
	t_u32			index;

	ray->tile.hit = intersection_w;
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
		ray->tile.tiles_index = index;
		ray->tile = zz_tile_values(ray, tiles, line);
		if (tiles[index].id == ray->tile_type_to_find)
			return (wx_true);
	}
	return (wx_false);
}

/*
** Find distance to horizontal wall, record floor, update ray values.
*/
static t_hit	zz_dist_horizontal_wall(t_ray *ray, t_map_tile *tiles)
{
	t_p2			intersection_w;
	t_u32			block_y;

	block_y = ray->start.y / WE_BLOCK_W;
	if (ray->angle_d > 180 && ray->angle_d < 360)
		block_y += 1;
	intersection_w.y = block_y * WE_BLOCK_W;
	ray->tiles_h_size = 0;
	while (intersection_w.y < ray->world_end_w && intersection_w.y >= 0)
	{
		intersection_w.x = (intersection_w.y - ray->b) / ray->k;
		if (intersection_w.x < 0 || intersection_w.x >= ray->world_end_w
			|| (ray->angle_d == 180 || ray->angle_d == 0 || ray->angle_d == 360)
			|| block_y >= WE_GRID_DIVIDE)
			break ;
		if ((zz_is_wall(tiles, ray, intersection_w, we_horisontal)))
			return (ray->tile);
		ray->tiles_h[ray->tiles_h_size] = ray->tile;
		ray->tiles_h_size++;
		intersection_w.y += WE_BLOCK_W;
		if (ray->angle_d < 180 && ray->angle_d > 0)
			intersection_w.y -= 2 * WE_BLOCK_W;
	}
	return (zz_tile_values(ray, tiles, we_no_wall));
}

/*
** Find distance to vertical wall, record floor, update ray values.
*/

static t_hit	zz_dist_vertical_wall(t_ray *ray, t_map_tile *tiles)
{
	t_p2			intersection_w;
	t_u32			block_x;

	block_x = ray->start.x / WE_BLOCK_W;
	if (ray->angle_d <= 90 || ray->angle_d >= 270)
		block_x += 1;
	intersection_w.x = block_x * WE_BLOCK_W;
	ray->tiles_v_size = 0;
	while (intersection_w.x < ray->world_end_w && intersection_w.x >= 0)
	{
		intersection_w.y = ray->k * intersection_w.x + ray->b;
		if (intersection_w.y < 0 || intersection_w.y >= ray->world_end_w
			|| (ray->angle_d == 90 || ray->angle_d == 270)
			|| block_x >= WE_GRID_DIVIDE)
			break ;
		if ((zz_is_wall(tiles, ray, intersection_w, we_vertical)))
			return (ray->tile);
		ray->tiles_v[ray->tiles_v_size] = ray->tile;
		ray->tiles_v_size++;
		intersection_w.x += WE_BLOCK_W;
		if (ray->angle_d > 90 && ray->angle_d < 270)
			intersection_w.x -= 2 * WE_BLOCK_W;
	}
	return (zz_tile_values(ray, tiles, we_no_wall));
}

/*
** Find the closest intersection point with horisontal and vertical
** walls. Choose the closer one to be drawn.
*/

void	we_ray_cast(t_ray *ray, t_map_tile *tiles)
{
	t_hit	horizontal;
	t_hit	vertical;

	horizontal = zz_dist_horizontal_wall(ray, tiles);
	vertical = zz_dist_vertical_wall(ray, tiles);
	if (vertical.distance < horizontal.distance)
	{
		ray->tile = vertical;
		if (vertical.distance == 0)
			ray->tile = horizontal;
	}
	else
	{
		ray->tile = horizontal;
		if (horizontal.distance == 0)
			ray->tile = vertical;
	}
}
