/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_depth_buffer_del.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: name <name@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:22:30 by name          #+#    #+#             */
/*   Updated: 2021/04/12 16:22:30 by name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

#include "wc_draw.h"

void	wc_depth_buffer_del(t_depth_buffer *db)
{
	free(db->data);
	wx_buffer_set(db, sizeof(*db), 0);
}
