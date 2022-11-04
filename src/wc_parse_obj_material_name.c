/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse_obj_material_name.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:41:38 by name          #+#    #+#             */
/*   Updated: 2021/04/12 22:26:00 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_parse.h"

t_bool	wc_parse_obj_material_name(t_parse_context *pc)
{
	if (!wx_parse_keyword(pc, "usemtl"))
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
