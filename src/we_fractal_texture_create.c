/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_fractal_texture_create.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:55:17 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/11 23:36:59 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

static t_s32	zz_fractal_color(t_s32 i, t_fractal *fractal, t_u32 id,
	t_u32 index)
{
	t_u32	color;
	t_rgba	modifier;

	color = 0;
	modifier.r = i * id * fractal->ptr_y;
	modifier.g = id * fractal->ptr_x;
	modifier.b = 40 * i;
	if (i < fractal->max_i)
	{
		index = index * 0.001f;
		color = 65536 * (90 + modifier.r) + (256 * 5 * i + modifier.g)
			+ (i + modifier.b) + index;
	}
	return (color);
}

static void	zz_init_fractal(t_fractal *fractal, t_s32 *h, t_s32 *w, t_p2 p)
{
	*h = WE_GRID_DIVIDE;
	*w = WE_GRID_DIVIDE;
	fractal->win_h = *h;
	fractal->win_w = *w;
	fractal->max_i = 20;
	fractal->min_x = -2.0;
	fractal->max_x = 2.0;
	fractal->min_y = 1.5;
	fractal->max_y = -1.5;
	fractal->zoom = 1;
	fractal->scale_x = (fractal->max_x - fractal->min_x) / (fractal->win_w);
	fractal->scale_y = (fractal->max_y - fractal->min_y) / (fractal->win_h);
	fractal->ptr_x += p.x / WE_GRID_DIVIDE;
	fractal->ptr_y += p.y / WE_GRID_DIVIDE;
}

t_tex	we_fractal_texture_create(t_p2 ray_start,
	t_s32 (*f)(t_s32, t_s32, t_fractal *), t_u32 id)
{
	t_tex		fractal;
	t_u32		x;
	t_u32		y;
	t_u32		i;
	t_fractal	fractal_values;

	y = 0;
	wx_buffer_set(&fractal_values, sizeof(t_fractal), 0);
	zz_init_fractal(&fractal_values, (t_s32 *)&fractal.height,
		(t_s32 *)&fractal.width, ray_start);
	while (y < fractal.height)
	{
		x = 0;
		while (x < fractal.width)
		{
			i = x + y * fractal.height;
			fractal.fractal[i] = zz_fractal_color(f(x, y, &fractal_values),
					&fractal_values, id, i);
			x++;
		}
		y++;
	}
	return (fractal);
}
