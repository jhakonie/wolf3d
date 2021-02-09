/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_init_chart.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 22:38:50 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/09 02:18:43 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"

void	we_init_chart(t_map *m)
{
	t_u32 i;

	i = 0;
	while (i < m->block_count)
	{
		m->chart[i].id = WE_ID_INIT;
		i++;
	}
}
