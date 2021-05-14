/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_parse_xpm_pixels.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 01:08:09 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/14 15:57:55 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_parse_xpm.h"

/*
** Parse the end of line or the end of image.
** Upon failure free saved colors and pixel-array.
*/

static t_bool	zz_parse_end_of_line(t_parse_context *pc, t_parse_xpm_index i,
	t_xpm *xpm)
{
	if (i.h < xpm->height - 1)
	{
		if (!wx_parse_keyword(pc, "\",\n\""))
			return (wx_parse_xpm_error(xpm, WX_XPM_FREE_PIXELS,
					"xpm-error: pixels, end of line: |\",\\n\"| missing.\n", 50));
	}
	else
	{
		if (!wx_parse_keyword(pc, "\""))
			return (wx_parse_xpm_error(xpm, WX_XPM_FREE_PIXELS,
					"xpm-error: pixels, end of line: |\"| missing.\n", 46));
		wx_parse_whitespace(pc);
		if (!wx_parse_keyword(pc, "};"))
			return (wx_parse_xpm_error(xpm, WX_XPM_FREE_PIXELS,
					"xpm-error: pixels, end of line: |};| missing.\n", 47));
		wx_parse_whitespace(pc);
	}
	return (wx_true);
}

static t_bool	zz_is_key(t_parse_context *pc, t_xpm *xpm, t_u32 table_index)
{
	t_u32		keyword_index;
	t_u32		keyword_end;

	keyword_index = 0;
	keyword_end = xpm->keyword_length - 1;
	while (xpm->table[table_index].key != WX_NULL && pc->p != pc->e
		&& keyword_index <= keyword_end
		&& *pc->p == xpm->table[table_index].key[keyword_index])
	{
		if (keyword_index == keyword_end)
		{
			pc->p++;
			return (wx_true);
		}
		pc->p++;
		keyword_index++;
	}
	pc->p -= keyword_index;
	return (wx_false);
}

/*
** Find the keyword matching the image key and save corresponding color.
*/

t_bool	zz_find_key(t_parse_context *pc, t_xpm *xpm, t_u32 pixel_index)
{
	t_u64			hash;
	t_u64			table_index;
	t_u32			color;
	t_bool			end_of_table;

	end_of_table = wx_false;
	hash = wx_parse_xpm_hash_key(pc->p, xpm->keyword_length);
	table_index = hash % xpm->table_size;
	while (table_index < xpm->table_size)
	{
		if (zz_is_key(pc, xpm, table_index))
			break ;
		table_index++;
		if (table_index == xpm->table_size && !end_of_table)
		{
			table_index = 0;
			end_of_table = wx_true;
		}
		else if (table_index == xpm->table_size && end_of_table)
			return (wx_false);
	}
	color = xpm->table[table_index].value;
	xpm->pixels[pixel_index] = color;
	return (wx_true);
}

/*
** Parse comment, allocate pixel-array. Free saved colors upon failure.
** Loop through xpm image comparing pixel keys to color keywords.
*/

t_bool	wx_parse_xpm_pixels(t_parse_context *pc, t_xpm *xpm)
{
	t_parse_xpm_index	i;

	xpm->pixels = (t_u32 *)malloc(xpm->height * xpm->width * sizeof(t_u32));
	if (!wx_parse_keyword(pc, "\"") || !xpm->pixels)
		return (wx_parse_xpm_error(xpm, WX_XPM_FREE_TABLE,
				"xpm-error: pixels start or malloc.\n", 36));
	i.pixel_index = 0;
	i.h = 0;
	while (i.h < xpm->height)
	{
		i.w = 0;
		while (i.w < xpm->width && pc->p != pc->e)
		{
			if (!zz_find_key(pc, xpm, i.pixel_index))
				return (wx_parse_xpm_error(xpm, WX_XPM_FREE_PIXELS,
						"xpm-error: no key found.\n", 26));
			i.pixel_index++;
			i.w++;
		}
		if (!zz_parse_end_of_line(pc, i, xpm))
			return (wx_false);
		i.h++;
	}
	return (wx_true);
}
