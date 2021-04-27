/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_fractal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:35:29 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/27 22:36:48 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

static void	zz_init_z(t_complex *z, t_s32 x, t_s32 y, t_fractal *fractal)
{
	double	after_zoom_x_f;
	double	after_zoom_y_f;
	double	offset_x_f;
	double	offset_y_f;

	after_zoom_y_f = fractal->scale_y
		* (fractal->zoom_y - fractal->zoom_y * fractal->zoom);
	after_zoom_x_f = fractal->scale_x
		* (fractal->zoom_x - fractal->zoom_x * fractal->zoom);
	offset_y_f = fractal->move_y + after_zoom_y_f + fractal->min_y;
	offset_x_f = fractal->move_x + after_zoom_x_f + fractal->min_x;
	z->y = -1.0 * (fractal->scale_y * y * fractal->zoom + offset_y_f);
	z->x = fractal->scale_x * x * fractal->zoom + offset_x_f;
}

static void	zz_init_c(t_complex *c, t_fractal *fractal)
{
	c->x = fractal->min_x + fractal->ptr_x * fractal->scale_x;
	c->y = fractal->max_y - fractal->ptr_y * fractal->scale_y;
}

t_s32	we_mandelbrot(t_s32 x, t_s32 y, t_fractal *fractal)
{
	t_s32			i;
	t_f32			n;
	t_complex		z;
	t_complex		c;

	i = 0;
	z.x = 0;
	z.y = 0;
	zz_init_z(&c, x, y, fractal);
	c.x -= 0.5;
	while (i < fractal->max_i)
	{
		z = we_c_plus(we_c_sqred(z), c);
		n = z.x * z.x + z.y * z.y;
		if (n > 4)
			break ;
		i++;
	}
	return (i);
}

t_s32	we_julia(t_s32 x, t_s32 y, t_fractal *fractal)
{
	t_complex		z;
	t_complex		c;
	t_s32			i;
	t_f32			n;

	i = 0;
	zz_init_c(&c, fractal);
	zz_init_z(&z, x, y, fractal);
	while (i < fractal->max_i)
	{
		z = we_c_plus(we_c_sqred(z), c);
		n = z.x * z.x + z.y * z.y;
		if (n > 4)
			break ;
		i++;
	}
	return (i);
}

t_s32	we_snowflake(t_s32 x, t_s32 y, t_fractal *fractal)
{
	t_s32		i;
	t_f32		n;
	t_complex	z;
	t_complex	a;

	i = 0;
	fractal->zoom = 2.0;
	zz_init_c(&a, fractal);
	zz_init_z(&z, x, y, fractal);
	while (i < fractal->max_i)
	{
		z.x = sinf(z.x) + i * 0.0001;
		z.y = sinf(z.y) + i * 0.0001;
		z = we_c_multiply((z), (we_c_sqred(z)));
		z = we_c_sqred(we_c_plus((a), we_c_sqred(z)));
		z = we_c_plus((a), we_c_sqred(z));
		n = z.x * z.x + z.y * z.y;
		if (n > 2)
			break ;
		i++;
	}
	return (i);
}

// t_s32	we_mandala(t_s32 x, t_s32 y, t_fractal *fractal)
// {
// 	t_complex	z;
// 	t_complex	c;
// 	t_s32		i;
// 	t_f32		n;

// 	i = 0;
// 	zz_init_c(&c, fractal);
// 	zz_init_z(&z, x, y, fractal);
// 	while (i < fractal->max_i)
// 	{
// 		z = we_c_multiply(we_c_multiply(we_c_plus(we_c_plus(we_c_divide
// 		(we_c_sqred(we_c_sqred(we_c_sqred(we_c_sqred(z)))), c),
// 		we_c_sqred(we_c_sqred(we_c_sqred(we_c_multiply
// 		(we_c_sqred(we_c_sqred(z)), z)))))
// 		, c), z), c);
// 		n = z.x * z.x + z.y * z.y;
// 		if (n > 1)
// 			break ;
// 		i++;
// 	}
// 	return (i);
// }
