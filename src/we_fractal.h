/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_fractal.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:18:59 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 20:58:28 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WE_FRACTAL_H
# define WE_FRACTAL_H

# include "wx_types.h"
# include "wx_math.h"

typedef struct s_complex
{
	double			x;
	double			y;
}					t_complex;

t_complex	we_c_sqred(t_complex a);
t_complex	we_c_divide(t_complex a, t_complex b);
t_complex	we_c_minus(t_complex a, t_complex b);
t_complex	we_c_multiply(t_complex a, t_complex b);
t_complex	we_c_plus(t_complex a, t_complex b);

typedef struct s_fractal
{
	int			win_h;
	int			win_w;
	double		max_y;
	double		min_y;
	double		max_x;
	double		min_x;
	int			max_i;
	double		move_x;
	double		move_y;
	double		ptr_x;
	double		ptr_y;
	int			zoom_x;
	int			zoom_y;
	double		zoom;
	double		scale_x;
	double		scale_y;
}					t_fractal;

t_s32		we_mandelbrot(t_s32 x, t_s32 y, t_fractal *all);
t_s32		we_julia(t_s32 x, t_s32 y, t_fractal *all);
t_s32		we_snowflake(t_s32 x, t_s32 y, t_fractal *all);

#endif
