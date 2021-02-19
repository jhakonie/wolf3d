/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_sleep_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 21:12:58 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/16 20:41:38 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"

#include "wx_time.h"

void	wx_sleep_s(t_f64 duration_s)
{
	struct timespec	ts;

	ts.tv_sec = (t_u64)duration_s;
	ts.tv_nsec = (duration_s - (t_u64)duration_s) * 1000000000.0;
	clock_nanosleep(CLOCK_REALTIME, 0, &ts, WX_NULL);
}
