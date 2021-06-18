#include "wx_draw.h"

static void	zz_ray_compass_direction(t_ray *ray)
{
	if ((ray->angle_d < 45 && ray->angle_d >= 0)
		|| (ray->angle_d <= 360 && ray->angle_d > 315))
	{
		ray->tile.side = we_vertical;
		ray->tile.compass = we_east;
	}
	else if (ray->angle_d >= 45 && ray->angle_d <= 135)
	{
		ray->tile.side = we_horisontal;
		ray->tile.compass = we_north;
	}
	else if (ray->angle_d > 135 && ray->angle_d < 225)
	{
		ray->tile.side = we_vertical;
		ray->tile.compass = we_west;
	}
	else if (ray->angle_d >= 225 && ray->angle_d <= 315)
	{
		ray->tile.side = we_horisontal;
		ray->tile.compass = we_south;
	}
}

static void	zz_raycast(t_ray *ray, t_f32 min_w, t_f32 max_w)
{
	if (ray->tile.compass == we_north)
	{
		ray->tile.hit.y = min_w;
		ray->tile.hit.x = (ray->tile.hit.y - ray->b) / ray->k;
	}
	else if (ray->tile.compass == we_south)
	{
		ray->tile.hit.y = max_w;
		ray->tile.hit.x = (ray->tile.hit.y - ray->b) / ray->k;
	}
	else if (ray->tile.compass == we_east)
	{
		ray->tile.hit.x = max_w;
		ray->tile.hit.y = ray->k * ray->tile.hit.x + ray->b;
	}
	else if (ray->tile.compass == we_west)
	{
		ray->tile.hit.x = min_w;
		ray->tile.hit.y = ray->k * ray->tile.hit.x + ray->b;
	}
}

t_hit	we_ray_cast_sky(t_ray *ray)
{
	t_f32	min_w;
	t_f32	max_w;

	min_w = -ray->world_end_w;
	max_w = ray->world_end_w * 2 - (2 * WX_TILE_WIDTH);
	zz_ray_compass_direction(ray);
	zz_raycast(ray, min_w, max_w);
	return (ray->tile);
}
