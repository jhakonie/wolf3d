/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_parse_xpm_colors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:56:28 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/14 16:34:48 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_parse_xpm.h"

/*
** Save hex to a string and parse that to uint.
** Colors' array is freed upon failure.
*/

static t_bool	zz_parse_hex(t_parse_context *pc, t_u32 *hex)
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

static t_u64	zz_find_table_index(t_parse_context *pc, t_xpm *xpm)
{
	t_u64	hash;
	t_u64	table_index;

	hash = wx_parse_xpm_hash_key(pc->p, xpm->keyword_length);
	table_index = hash % xpm->table_size;
	while (xpm->table[table_index].key != WX_NULL)
	{
		table_index++;
		if (table_index == xpm->table_size)
			table_index = 0;
	}
	return (table_index);
}

/*
** Parse possible comment. If line doesn't start with ", free colors' array.
** Parse color keys and corresponding colors and save them. Parse comment.
*/
/*
** 2021-05-03 todo: think about all the spots where to use wx_parse_whitespace()
*/
t_bool	wx_parse_xpm_colors(t_parse_context *pc, t_xpm *xpm)
{
	t_u32	i;
	t_u64	table_index;

	i = 0;
	wx_parse_xpm_comment(pc);
	while (i <= xpm->color_count - 1 && pc->p != pc->e)
	{
		if (!wx_parse_keyword(pc, "\""))
			return (wx_parse_xpm_error(xpm, WX_XPM_FREE_TABLE,
					"xpm-error: color definition start of line.\n", 44));
		table_index = zz_find_table_index(pc, xpm);
		xpm->table[table_index].key = pc->p;
		pc->p += xpm->keyword_length;
		if (!wx_parse_whitespace(pc) || !wx_parse_keyword(pc, "c")
			|| !wx_parse_whitespace(pc) || !wx_parse_keyword(pc, "#")
			|| !zz_parse_hex(pc, &xpm->table[table_index].value)
			|| !wx_parse_keyword(pc, "\",\n"))
			return (wx_false);
		i++;
	}
	wx_parse_xpm_comment(pc);
	return (wx_true);
}
