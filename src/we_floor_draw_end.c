/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_floor_draw_end.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 17:54:14 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/08 21:37:16 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

static t_p2	zz_north(t_ray *ray, t_p2 block)
{
	t_p2	end;

	if (ray->angle_d <= 90)
	{
		end.x = (block.x + 1) * WE_BLOCK_W;
		end.y = ray->k * end.x + ray->b;
		if (end.y < ((block.y - 1) * WE_BLOCK_W))
		{
			end.y = (block.y - 1) * WE_BLOCK_W;
			end.x = (end.y - ray->b) / ray->k;
		}
		return (end);
	}
	else
	{
		end.x = (block.x) * WE_BLOCK_W;
		end.y = ray->k * end.x + ray->b;
		if (end.y < ((block.y - 1) * WE_BLOCK_W))
		{
			end.y = (block.y - 1) * WE_BLOCK_W;
			end.x = (end.y - ray->b) / ray->k;
		}
	}
	return (end);
}

static t_p2	zz_south(t_ray *ray, t_p2 block)
{
	t_p2	end;

	if (ray->angle_d >= 270)
	{
		end.x = (block.x + 1) * WE_BLOCK_W;
		end.y = ray->k * end.x + ray->b;
		if (end.y >= ((block.y + 1) * WE_BLOCK_W))
		{
			end.y = (block.y + 1) * WE_BLOCK_W;
			end.x = (end.y - ray->b) / ray->k;
		}
		return (end);
	}
	else
	{
		end.x = (block.x) * WE_BLOCK_W;
		end.y = ray->k * end.x + ray->b;
		if (end.y > ((block.y + 1) * WE_BLOCK_W))
		{
			end.y = (block.y + 1) * WE_BLOCK_W;
			end.x = (end.y - ray->b) / ray->k;
		}
	}
	return (end);
}

static t_p2	zz_east(t_ray *ray, t_p2 block)
{
	t_p2	end;

	if (ray->angle_d >= 0 && ray->angle_d <= 90)
	{
		end.y = (block.y) * WE_BLOCK_W;
		end.x = (end.y - ray->b) / ray->k;
		if (ray->angle_d == 45)
			return (end);
		if (end.x > ((block.x + 1) * WE_BLOCK_W))
		{
			end.x = (block.x + 1) * WE_BLOCK_W;
			end.y = ray->k * end.x + ray->b;
		}
	}
	else
	{
		end.y = (block.y + 1) * WE_BLOCK_W;
		end.x = (end.y - ray->b) / ray->k;
		if (end.x > ((block.x + 1) * WE_BLOCK_W))
		{
			end.x = (block.x + 1) * WE_BLOCK_W;
			end.y = ray->k * end.x + ray->b;
		}
	}
	return (end);
}

static t_p2	zz_west(t_ray *ray, t_p2 block)
{
	t_p2	end;

	if (ray->angle_d < 180)
	{
		end.y = (block.y) * WE_BLOCK_W;
		end.x = (end.y - ray->b) / ray->k;
		if (end.x < ((block.x - 1) * WE_BLOCK_W))
		{
			end.x = (block.x - 1) * WE_BLOCK_W;
			end.y = ray->k * end.x + ray->b;
		}
		return (end);
	}
	else
	{
		end.y = (block.y + 1) * WE_BLOCK_W;
		end.x = (end.y - ray->b) / ray->k;
		if (end.x < ((block.x - 1) * WE_BLOCK_W))
		{
			end.x = (block.x - 1) * WE_BLOCK_W;
			end.y = ray->k * end.x + ray->b;
		}
		return (end);
	}
}

t_p2	we_floor_draw_end(t_ray *ray)
{
	t_p2	block;
	t_p2	end;

	block.x = (int)(ray->tile.hit.x / WE_BLOCK_W);
	block.y = (int)(ray->tile.hit.y / WE_BLOCK_W);
	if (ray->tile.compass == we_north)
		end = zz_north(ray, block);
	else if (ray->tile.compass == we_south)
		end = zz_south(ray, block);
	else if (ray->tile.compass == we_east)
		end = zz_east(ray, block);
	else
		end = zz_west(ray, block);
	if (end.x < 0)
		end.x = 0;
	else if (end.x > (float)ray->world_end_w)
		end.x = (float)ray->world_end_w;
	if (end.y < 0)
		end.y = 0;
	else if (end.y > (float)ray->world_end_w - 1)
		end.y = (float)ray->world_end_w - 1;
	return (end);
}
