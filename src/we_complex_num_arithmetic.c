/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_complex_num_arithmetic.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:38:56 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 21:52:23 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

t_complex	we_c_sqred(t_complex a)
{
	t_complex	res;

	res.x = a.x * a.x - a.y * a.y;
	res.y = 2 * a.x * a.y;
	return (res);
}

t_complex	we_c_divide(t_complex a, t_complex b)
{
	t_complex	res;

	res.x = (a.x * b.x + a.y * b.y) / (b.x * b.x + b.y * b.y);
	res.y = (-a.x * b.y + b.x * a.y) / (b.x * b.x + b.y * b.y);
	return (res);
}

t_complex	we_c_minus(t_complex a, t_complex b)
{
	t_complex	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return (res);
}

t_complex	we_c_multiply(t_complex a, t_complex b)
{
	t_complex	res;

	res.x = a.x * b.x - a.y * b.y;
	res.y = a.x * b.y + a.y * b.x;
	return (res);
}

t_complex	we_c_plus(t_complex a, t_complex b)
{
	t_complex	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return (res);
}
