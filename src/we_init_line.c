/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_init_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 00:04:56 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 20:51:52 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

void	we_init_line(t_p2 a, t_p2 b, t_line *l)
{
	l->start = a;
	l->end = b;
	l->delta.x = b.x - a.x;
	l->delta.y = b.y - a.y;
	if (l->delta.x == 0)
		l->k = 0;
	else
		l->k = l->delta.y / l->delta.x;
	l->b = -l->k * l->start.x + l->start.y;
}
