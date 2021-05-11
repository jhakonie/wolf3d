/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_parse_until.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:53:27 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 22:52:26 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_parse.h"

t_bool	wx_parse_until(t_parse_context *pc, t_u8 c)
{
	char const	*b;

	b = pc->p;
	while (pc->p < pc->e)
	{
		if (*pc->p == c)
		{
			pc->p++;
			return (wx_true);
		}
		pc->p++;
	}
	if (pc->p == pc->e)
		pc->p = b;
	return (wx_false);
}
