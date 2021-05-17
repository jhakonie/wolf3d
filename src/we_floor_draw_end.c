/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_floor_draw_end.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 17:54:14 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/14 21:39:20 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

static t_p2	zz_north(t_ray ray, t_p2 block)
{
	t_p2	end;

	if (ray.angle_d < 90)
	{
		end.x = (block.x + 1) * WE_BLOCK_W;
		end.y = ray.k * end.x + ray.b;
		if (end.y < ((block.y - 1) * WE_BLOCK_W))
		{
			end.y = (block.y - 1) * WE_BLOCK_W;
			end.x = (end.y - ray.b) / ray.k;
		}
		return (end);
	}
	end.x = (block.x) * WE_BLOCK_W;
	end.y = ray.k * end.x + ray.b;
	if (end.y < ((block.y - 1) * WE_BLOCK_W))
	{
		end.y = (block.y - 1) * WE_BLOCK_W;
		end.x = (end.y - ray.b) / ray.k;
	}
	return (end);
}

static t_p2	zz_south(t_ray ray, t_p2 block)
{
	t_p2	end;

	if (ray.angle_d >= 270)
	{
		end.x = (block.x + 1) * WE_BLOCK_W;
		end.y = ray.k * end.x + ray.b;
		if (end.y > ((block.y + 1) * WE_BLOCK_W))
		{
			end.y = (block.y + 1) * WE_BLOCK_W;
			end.x = (end.y - ray.b) / ray.k;
		}
		return (end);
	}
	end.x = (block.x) * WE_BLOCK_W;
	end.y = ray.k * end.x + ray.b;
	if (end.y > ((block.y + 1) * WE_BLOCK_W))
	{
		end.y = (block.y + 1) * WE_BLOCK_W;
		end.x = (end.y - ray.b) / ray.k;
	}
	return (end);
}

static t_p2	zz_east(t_ray ray, t_p2 block)
{
	t_p2	end;

	wx_buffer_set(&end, sizeof(t_p2), 0);
	if (ray.angle_d >= 0 && ray.angle_d <= 90)
	{
		end.y = (block.y) * WE_BLOCK_W;
		end.x = (end.y - ray.b) / ray.k;
		if (end.x > ((block.x + 1) * WE_BLOCK_W))
		{
			end.x = (block.x + 1) * WE_BLOCK_W;
			end.y = ray.k * end.x + ray.b;
		}
		return (end);
	}
	else if (ray.angle_d < 360 && ray.angle_d >= 270)
	{
		end.y = (block.y + 1) * WE_BLOCK_W;
		end.x = (end.y - ray.b) / ray.k;
		if (end.x > ((block.x + 1) * WE_BLOCK_W))
		{
			end.x = (block.x + 1) * WE_BLOCK_W;
			end.y = ray.k * end.x + ray.b;
		}
	}
	return (end);
}

static t_p2	zz_west(t_ray ray, t_p2 block)
{
	t_p2	end;

	if (ray.angle_d < 180)
	{
		end.y = (block.y) * WE_BLOCK_W;
		end.x = (end.y - ray.b) / ray.k;
		if (end.x < ((block.x - 1) * WE_BLOCK_W))
		{
			end.x = (block.x - 1) * WE_BLOCK_W;
			end.y = ray.k * end.x + ray.b;
		}
		return (end);
	}
	end.y = (block.y + 1) * WE_BLOCK_W;
	end.x = (end.y - ray.b) / ray.k;
	if (end.x < ((block.x - 1) * WE_BLOCK_W))
	{
		end.x = (block.x - 1) * WE_BLOCK_W;
		end.y = ray.k * end.x + ray.b;
	}
	return (end);
}

t_p2	we_floor_draw_end(t_ray ray)
{
	t_p2	block;

	block.x = (int)(ray.wall.end.x / WE_BLOCK_W);
	block.y = (int)(ray.wall.end.y / WE_BLOCK_W);
	if (ray.wall.compass == we_north)
		return (zz_north(ray, block));
	else if (ray.wall.compass == we_south)
		return (zz_south(ray, block));
	else if (ray.wall.compass == we_east)
		return (zz_east(ray, block));
	else
		return (zz_west(ray, block));
}
