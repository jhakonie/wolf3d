/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_ray_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:25:44 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/30 13:21:49 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_draw.h"

/*
** Calculate distance from palyer to wall and wall's projected height.
** Define side that was hit and wall's compass direction.
*/

static t_hit	zz_tile_values(t_ray *ray, t_u32 *tiles, t_side side)
{
	t_p2	delta;

	if (side == we_no_wall)
	{
		wx_buffer_set(&ray->tile, sizeof(t_hit), 0);
		return (ray->tile);
	}
	ray->tile.side = side;
	ray->tile.tiles_id = tiles[ray->tile.tiles_index];
	ray->tile.compass = wx_wall_compass_direction(ray->angle_d, side);
	if (ray->target_tile == 2 && ray->tile.tiles_id == 2)
		wx_draw_door_distance(ray);
	delta.x = ray->tile.hit.x - ray->start.x;
	delta.y = ray->tile.hit.y - ray->start.y;
	ray->tile.distance = sqrtf(delta.x * delta.x + delta.y * delta.y);
	ray->tile.distance *= cosf(wx_to_radians(ray->angle_to_player_d));
	ray->tile.projected_height = (ray->dist_to_screen_w / ray->tile.distance)
		* WX_TILE_WIDTH;
	return (ray->tile);
}

/*
** Check if the previously found ray-map-line-intersection point
** is inside a wall.
** Update tile values: side that was hit, compass direction
** of hit tile, distance of hit tile from player, projected height of tile
** on screen/projection plane.
** If the tile, that is hit, is a wall or an enemy or if
** target_tile is door
** and the tile hit is a door, return true and end raycast.
*/

static t_bool	zz_is_wall(t_u32 *tiles, t_ray *ray, t_p2 intersection_w,
	t_side line)
{
	t_u32			block_y;
	t_u32			block_x;
	t_u32			index;

	ray->tile.hit = intersection_w;
	block_y = intersection_w.y / WX_TILE_WIDTH;
	block_x = intersection_w.x / WX_TILE_WIDTH;
	index = block_x + block_y * WX_MAP_TILES_WIDTH;
	if (block_x >= WX_MAP_TILES_WIDTH || block_y >= WX_MAP_TILES_WIDTH
		|| (block_x == 0 && line == we_vertical))
		return (wx_false);
	if (ray->angle_d <= 180 && ray->angle_d >= 0 && line == we_horisontal)
		index -= WX_MAP_TILES_WIDTH;
	else if (ray->angle_d >= 90 && ray->angle_d <= 270 && line == we_vertical)
		index -= 1;
	if (index < WX_MAP_SIZE)
	{
		ray->tile.tiles_index = index;
		ray->tile = zz_tile_values(ray, tiles, line);
		if (((tiles[index] == 1 || tiles[index] == 2) && ray->target_tile == 7)
			|| (ray->target_tile == 2 && tiles[index] == 1)
			|| tiles[index] == ray->target_tile)
			return (wx_true);
	}
	return (wx_false);
}

/*
** Find distance to horizontal wall, record floor, update ray values.
*/

static t_hit	zz_dist_horizontal_wall(t_ray *ray, t_u32 *tiles)
{
	t_p2			intersection_w;
	t_u32			block_y;

	block_y = ray->start.y / WX_TILE_WIDTH;
	if (ray->angle_d > 180 && ray->angle_d < 360)
		block_y += 1;
	intersection_w.y = block_y * WX_TILE_WIDTH;
	ray->tiles_h_size = 0;
	while (intersection_w.y < ray->world_end_w && intersection_w.y >= 0)
	{
		intersection_w.x = (intersection_w.y - ray->b) / ray->k;
		if (intersection_w.x < 0 || intersection_w.x >= ray->world_end_w
			|| (ray->angle_d == 180 || ray->angle_d == 0 || ray->angle_d == 360)
			|| block_y >= WX_MAP_TILES_WIDTH)
			break ;
		if ((zz_is_wall(tiles, ray, intersection_w, we_horisontal)))
			return (ray->tile);
		ray->tiles_h[ray->tiles_h_size] = ray->tile;
		ray->tiles_h_size++;
		intersection_w.y += WX_TILE_WIDTH;
		if (ray->angle_d < 180 && ray->angle_d > 0)
			intersection_w.y -= 2 * WX_TILE_WIDTH;
	}
	return (zz_tile_values(ray, tiles, we_no_wall));
}

/*
** Find distance to vertical wall, record floor, update ray values.
*/

static t_hit	zz_dist_vertical_wall(t_ray *ray, t_u32 *tiles)
{
	t_p2			intersection_w;
	t_u32			block_x;

	block_x = ray->start.x / WX_TILE_WIDTH;
	if (ray->angle_d <= 90 || ray->angle_d >= 270)
		block_x += 1;
	intersection_w.x = block_x * WX_TILE_WIDTH;
	ray->tiles_v_size = 0;
	while (intersection_w.x < ray->world_end_w && intersection_w.x >= 0)
	{
		intersection_w.y = ray->k * intersection_w.x + ray->b;
		if (intersection_w.y < 0 || intersection_w.y >= ray->world_end_w
			|| (ray->angle_d == 90 || ray->angle_d == 270)
			|| block_x >= WX_MAP_TILES_WIDTH)
			break ;
		if ((zz_is_wall(tiles, ray, intersection_w, we_vertical)))
			return (ray->tile);
		ray->tiles_v[ray->tiles_v_size] = ray->tile;
		ray->tiles_v_size++;
		intersection_w.x += WX_TILE_WIDTH;
		if (ray->angle_d > 90 && ray->angle_d < 270)
			intersection_w.x -= 2 * WX_TILE_WIDTH;
	}
	return (zz_tile_values(ray, tiles, we_no_wall));
}

/*
** Find the closest intersection point with horisontal and vertical
** walls by calculating the intersection point of the ray and the
** horizontal/vertical map-grid-lines.
** Choose the closer wall of the found ones to be drawn.
*/

void	wx_ray_cast(t_ray *ray, t_u32 *tiles)
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
