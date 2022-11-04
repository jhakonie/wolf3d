/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse_obj_material_filename.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:14:17 by name          #+#    #+#             */
/*   Updated: 2021/04/12 22:26:00 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_parse.h"

t_bool	wc_parse_obj_material_filename(t_parse_context *pc)
{
	if (!wx_parse_keyword(pc, "mtllib"))
	{
		return (wx_false);
	}
	if (!wx_parse_whitespace(pc))
	{
		return (wx_false);
	}
	while (pc->p < pc->e)
	{
		if (*(t_s8 *)pc->p == '\n')
		{
			++pc->p;
			break ;
		}
		++pc->p;
	}
	return (wx_true);
}
