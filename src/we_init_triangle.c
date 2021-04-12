/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_init_triangle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:32:44 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 20:51:30 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

static void	zz_sort_by_x(t_p2 *points, t_p2 a, t_p2 b, t_p2 c)
{
	points[we_min] = a;
	points[we_mid] = b;
	points[we_max] = c;
	if (points[we_min].x > points[we_mid].x)
	{
		points[we_mid] = a;
		points[we_min] = b;
	}
	if (points[we_mid].x > points[we_max].x)
	{
		points[we_max] = points[we_mid];
		points[we_mid] = c;
		if (points[we_min].x > points[we_mid].x)
		{
			points[we_mid] = points[we_min];
			points[we_min] = c;
		}
	}
}

void	we_init_triangle(t_p2 a, t_p2 b, t_p2 c, t_triangle *t)
{
	t->a = a;
	t->b = b;
	t->c = c;
	t->color = 0;
	zz_sort_by_x(t->points, t->a, t->b, t->c);
	we_init_line(t->points[we_min], t->points[we_mid], &t->min_mid);
	we_init_line(t->points[we_min], t->points[we_max], &t->min_max);
	we_init_line(t->points[we_mid], t->points[we_max], &t->mid_max);
}
