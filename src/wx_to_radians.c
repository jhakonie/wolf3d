/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_to_radians.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: name <name@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:29:14 by name          #+#    #+#             */
/*   Updated: 2021/03/03 16:29:25 by name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_math.h"

t_f32	wx_to_radians(t_f32 deg)
{
	return (deg * (WX_PI / 180.0f));
}
