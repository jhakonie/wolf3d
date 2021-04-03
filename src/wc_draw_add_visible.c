/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw_add_visible.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 01:45:06 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/04/02 01:45:06 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_draw.h"

void	wc_draw_add_visible(t_draw_context *dc, t_clip_context const *cc)
{
	t_u16	*indices;
	t_u64	*indices_size;

	indices = dc->buffers->visible_indices;
	indices_size = &dc->buffers->visible_indices_size;
	if (cc->out_indices_size == 3)
	{
		indices[*indices_size + 0] = cc->out_indices[0];
		indices[*indices_size + 1] = cc->out_indices[1];
		indices[*indices_size + 2] = cc->out_indices[2];
		*indices_size += 3;
	}
	else if (cc->out_indices_size == 4)
	{
		indices[*indices_size + 0] = cc->out_indices[0];
		indices[*indices_size + 1] = cc->out_indices[1];
		indices[*indices_size + 2] = cc->out_indices[2];
		*indices_size += 3;
		indices[*indices_size + 0] = cc->out_indices[2];
		indices[*indices_size + 1] = cc->out_indices[3];
		indices[*indices_size + 2] = cc->out_indices[0];
		*indices_size += 3;
	}
}
