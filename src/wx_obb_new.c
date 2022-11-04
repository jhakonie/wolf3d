/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_obb_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: name <name@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:16:46 by name          #+#    #+#             */
/*   Updated: 2021/03/22 16:16:46 by name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_math.h"

/*
** 2021-03-21 todo: b_from_a expected/required to be orthonormal? presumably the
** average view_from_object matrix is that. if not shenanigans will ensue
*/

t_obb	wx_obb_new(t_aabb const *aabb, t_m44 const *b_from_a)
{
	t_obb	obb;

	obb.center = (t_p3){0.5 * (aabb->max.x + aabb->min.x),
		0.5 * (aabb->max.y + aabb->min.y), 0.5 * (aabb->max.z + aabb->min.z)};
	obb.center = wx_m44_mul_p3(b_from_a, &obb.center);
	obb.axes[0] = (t_n3){b_from_a->xs[0], b_from_a->xs[1], b_from_a->xs[2]};
	obb.axes[1] = (t_n3){b_from_a->xs[4], b_from_a->xs[5], b_from_a->xs[6]};
	obb.axes[2] = (t_n3){b_from_a->xs[8], b_from_a->xs[9], b_from_a->xs[10]};
	obb.extents2[0] = 0.5 * (aabb->max.x - aabb->min.x);
	obb.extents2[1] = 0.5 * (aabb->max.y - aabb->min.y);
	obb.extents2[2] = 0.5 * (aabb->max.z - aabb->min.z);
	return (obb);
}
