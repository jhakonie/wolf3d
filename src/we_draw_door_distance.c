#include "we_editor.h"

void	we_draw_door_distance(t_ray *ray)
{
	if (ray->tile.compass == we_north)
	{
		ray->tile.hit.y -= 0.5f * WX_TILE_WIDTH;
		ray->tile.hit.x = (ray->tile.hit.y - ray->b) / ray->k;
	}
	else if (ray->tile.compass == we_east)
	{
		ray->tile.hit.x += 0.5f * WX_TILE_WIDTH;
		ray->tile.hit.y = ray->tile.hit.x * ray->k + ray->b;
	}
	else if (ray->tile.compass == we_south)
	{
		ray->tile.hit.y += 0.5f * WX_TILE_WIDTH;
		ray->tile.hit.x = (ray->tile.hit.y - ray->b) / ray->k;
	}
	else if (ray->tile.compass == we_west)
	{
		ray->tile.hit.x -= fabsf(0.5f * WX_TILE_WIDTH);
		ray->tile.hit.y = fabsf(ray->tile.hit.x * ray->k + ray->b);
	}
	if (ray->tile.hit.x < 0 || ray->tile.hit.x > WX_MAP_SIZE)
		ray->tile.hit.x = -1;
	if (ray->tile.hit.y < 0 || ray->tile.hit.y > WX_MAP_SIZE)
		ray->tile.hit.y = -1;
}
