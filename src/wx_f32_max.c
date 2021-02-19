/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_f32_max.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:39:57 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/18 00:40:26 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_types.h"

t_f32	wx_f32_max(t_f32 x0, t_f32 x1)
{
	if (x0 > x1)
	{
		return (x0);
	}
	return (x1);
}