/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_time_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 20:30:26 by name          #+#    #+#             */
/*   Updated: 2021/02/24 21:13:01 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"

#include "wx_time.h"

t_f64	wx_time_s(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_REALTIME, &ts);
	return ((t_f64)ts.tv_sec + ((t_f64)ts.tv_nsec / 1000000000.0));
}
