/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_parse_xpm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:56:08 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/17 02:03:09 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_parse_xpm.h"
#include "stdio.h"

/* todo: remove <stdio.h> from draw.h */

/*
** Parse unsigned int.
*/

t_bool	zz_parse_u32(t_parse_context *pc, t_u32 *num)
{
	t_u32		integer;
	char const	*start;

	start = pc->p;
	integer = 0;
	while (pc->p < pc->e && *pc->p >= '0' && *pc->p <= '9')
	{
		integer = 10 * integer + (*pc->p - '0');
		pc->p++;
	}
	if (pc->p == start)
		return (wx_false);
	*num = integer;
	return (wx_true);
}

/*
** Parse width, height, color count, color key length and possible comment.
** Allocate table for colors.
*/

static t_bool	zz_parse_info(t_parse_context *pc, t_xpm *xpm)
{
	if (wx_parse_keyword(pc, "\"")
		&& zz_parse_u32(pc, &xpm->width) && wx_parse_whitespace(pc)
		&& zz_parse_u32(pc, &xpm->height) && wx_parse_whitespace(pc)
		&& zz_parse_u32(pc, &xpm->color_count) && wx_parse_whitespace(pc)
		&& zz_parse_u32(pc, &xpm->keyword_length)
		&& wx_parse_keyword(pc, "\",\n"))
	{
		xpm->size = xpm->width * xpm->height;
		xpm->table_size = xpm->color_count * 2;
		xpm->table
			= (t_key_value *)malloc(sizeof(t_key_value) * xpm->table_size);
		if (!xpm->table)
			return (wx_parse_xpm_error(xpm, 0,
					"xpm-error: parse info, malloc for table\n", 41));
		wx_buffer_set(xpm->table, sizeof(t_key_value) * xpm->table_size, 0);
		wx_parse_xpm_comment(pc);
		return (wx_true);
	}
	return (wx_parse_xpm_error(xpm, 0, "xpm-error: parse info\n", 23));
}

static t_bool	zz_free_txt(t_c8s *txt)
{
	free(txt->buffer);
	txt->buffer = WX_NULL;
	return (wx_false);
}

/*
** Parse declaration and possible comments.
*/

static t_bool	zz_parse_declaration(t_parse_context *pc, t_c8s *txt)
{
	if (wx_parse_keyword(pc, "static")
		&& wx_parse_whitespace(pc)
		&& wx_parse_keyword(pc, "char")
		&& wx_parse_whitespace(pc)
		&& wx_parse_keyword(pc, "*")
		&& wx_parse_until(pc, '{')
		&& wx_parse_whitespace(pc))
	{
		wx_parse_xpm_comment(pc);
		wx_parse_whitespace(pc);
		wx_parse_xpm_comment(pc);
		return (wx_true);
	}
	zz_free_txt(txt);
	return (wx_false);
}

/*
** Read file into buffer, check if file's first row is valid,
** parse declaration and save image info.
** Free buffer upon failure.
*/

t_bool	wx_parse_xpm(t_c8 const *filename, t_xpm *xpm)
{
	t_parse_context	pc;
	t_c8s			txt;

	if (!wx_c8s_new_from_file(&txt, 1024, filename))
		return (wx_false);
	pc.p = (t_c8 const *)txt.buffer;
	pc.e = (t_c8 const *)(txt.buffer + txt.size);
	if ((wx_parse_keyword(&pc, "/* XPM */\n")))
	{
		if (!zz_parse_declaration(&pc, &txt))
			return (wx_parse_xpm_error(xpm, 0,
					"xpm-parse error: declaration.\n", 31));
		write(1, "loading texture...", 19);
		if (!zz_parse_info(&pc, xpm)
			|| !wx_parse_xpm_colors(&pc, xpm)
			|| !wx_parse_xpm_pixels(&pc, xpm))
			return (zz_free_txt(&txt));
		if (pc.p != pc.e)
			return (wx_parse_xpm_error(xpm, WX_XPM_FREE_PIXELS,
					"xpm-parse error: end of file.\n", 31));
		zz_free_txt(&txt);
		return (wx_true);
	}
	zz_free_txt(&txt);
	return (wx_false);
}
