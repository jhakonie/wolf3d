/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_parse_xpm_colors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:56:28 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 22:53:40 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_parse_xpm.h"

/*
** Save hexa to a string and parse that to uint.
** Colors' array is freed upon failure.
*/

static t_bool	zz_parse_hexa(t_parse_context *pc, t_u32 *hex)
{
	t_u8	numbers[6];
	t_u32	i;

	i = 0;
	while (i < 6 && pc->p != pc->e)
	{
		numbers[i] = *pc->p;
		i++;
		pc->p++;
	}
	if (!wx_parse_hex(numbers, hex, 6))
		return (wx_false);
	return (wx_true);
}

/*
** Parse possible comment. If line doesn't start with ", free colors' array.
** Parse color keys and corresponding colors and save them. Parse comment.
** Free allocated colors upon failure.
*/
/*
** 2021-05-03 todo: think about all the spots where to use wx_parse_whitespace()
*/
t_bool	wx_parse_xpm_colors(t_xpm *xpm, t_parse_context *pc)
{
	t_u32	i;

	i = 0;
	wx_parse_xpm_comment(pc);
	if (!wx_parse_keyword(pc, "\""))
		return (wx_parse_xpm_error(xpm, WX_XPM_FREE_KEY, i));
	while (i <= xpm->color_count - 1 && pc->p != pc->e)
	{
		xpm->key[i].keyword
			= (t_u8 *)malloc(sizeof(t_u8) * xpm->keyword_length);
		if (!xpm->key[i].keyword)
			return (wx_parse_xpm_error(xpm, WX_XPM_FREE_KEYWORD, i));
		wx_buffer_copy(xpm->key[i].keyword, pc->p, xpm->keyword_length);
		pc->p += xpm->keyword_length;
		if (!wx_parse_whitespace(pc) || !wx_parse_keyword(pc, "c #")
			|| !zz_parse_hexa(pc, &xpm->key[i].color)
			|| !wx_parse_keyword(pc, "\",\n"))
			return (wx_parse_xpm_error(xpm, WX_XPM_FREE_KEYWORD, i));
		if (i < xpm->color_count - 1 && !wx_parse_keyword(pc, "\""))
			return (wx_parse_xpm_error(xpm, WX_XPM_FREE_KEYWORD, i));
		i++;
	}
	wx_parse_xpm_comment(pc);
	return (wx_true);
}
