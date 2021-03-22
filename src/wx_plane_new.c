/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_plane_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 07:59:01 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/20 08:00:17 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

#include "wx_math.h"

t_plane		wx_plane_new(t_f32 a, t_f32 b, t_f32 c, t_f32 d)
{
	t_f32	k;
	t_plane	pl;

	k = 1.0f / sqrtf(a * a + b * b + c * c);
	pl.n = (t_n3){k * a, k * b, k * c};
	pl.d = k * d;
	return (pl);
}