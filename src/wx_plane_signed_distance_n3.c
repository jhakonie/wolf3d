/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_plane_signed_distance_n3.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: name <name@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:11:13 by name          #+#    #+#             */
/*   Updated: 2021/03/22 16:11:13 by name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_math.h"

t_f32	wx_plane_signed_distance_n3(t_plane const *p, t_n3	const *n)
{
	return (p->n.x * n->x + p->n.y * n->y + p->n.z);
}
