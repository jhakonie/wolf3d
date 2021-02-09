/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_chart_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:18:09 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/09 00:12:08 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

t_bool	we_chart_new(t_map *m)
{
	t_u32 size;

	size = WE_GRID_DIVIDE * WE_GRID_DIVIDE;
	if (!(m->chart = (t_item *)malloc(sizeof(t_item) * size)))
		return (wx_false);
	wx_buffer_set(m->chart, size * sizeof(t_item), 0);
	return (wx_true);
}
