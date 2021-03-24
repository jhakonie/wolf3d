/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_chart_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:18:09 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/24 15:04:00 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

t_bool	we_chart_new(t_map *m)
{
	t_u64	size;

	size = WE_GRID_DIVIDE * WE_GRID_DIVIDE;
	m->chart = (t_item *)malloc(sizeof(t_item) * size);
	if (!m->chart)
		return (wx_false);
	wx_buffer_set(m->chart, sizeof(t_item) * size, 0);
	return (wx_true);
}
