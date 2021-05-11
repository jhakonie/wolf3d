/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_parse_xpm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:56:08 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 22:54:54 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_parse_xpm.h"

/* todo: remove <stdio.h> from draw.h */

/*
** Parse image width, height, color count and color key length
** Allocate array for colors.
*/

static t_bool	zz_parse_info(t_xpm *xpm, t_parse_context *pc)
{
	t_f32	info[4];

	wx_buffer_set(info, sizeof(t_f32), 0);
	if (wx_parse_f32(pc, &info[0])
		&& wx_parse_whitespace(pc)
		&& wx_parse_f32(pc, &info[1])
		&& wx_parse_whitespace(pc)
		&& wx_parse_f32(pc, &info[2])
		&& wx_parse_whitespace(pc)
		&& wx_parse_f32(pc, &info[3])
		&& wx_parse_keyword(pc, "\",\n"))
	{
		xpm->width = (int)info[0];
		xpm->height = (int)info[1];
		xpm->color_count = (int)info[2];
		xpm->keyword_length = (int)info[3];
		xpm->key
			= (t_color_key *)malloc(sizeof(t_color_key) * xpm->color_count);
		if (!xpm->key)
			return (wx_false);
		return (wx_true);
	}
	return (wx_false);
}

/*
** Parse declaration and possible comments.
*/

static t_bool	zz_parse_declaration(t_parse_context *pc)
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
		if (!wx_parse_keyword(pc, "\""))
			return (wx_false);
		return (wx_true);
	}
	return (wx_false);
}

static t_bool	zz_free_txt(t_c8s *txt)
{
	free(txt->buffer);
	txt->buffer = WX_NULL;
	return (wx_false);
}

/*
** Read file into buffer, check if file type is valid,
** parse declaration and save image info.
** Free buffer upon failure.
*/

t_bool	wx_parse_xpm(char const *filename, t_xpm *xpm)
{
	t_parse_context	pc;
	t_c8s			txt;

	if (!wx_c8s_new_from_file(&txt, 1024, filename))
		return (wx_false);
	pc.p = (char const *)txt.buffer;
	pc.e = (char const *)(txt.buffer + txt.size);
	if ((wx_parse_keyword(&pc, "/* XPM */\n")))
	{
		if (!zz_parse_declaration(&pc))
			return (zz_free_txt(&txt));
		write(1, "loading texture...", 19);
		if (!zz_parse_info(xpm, &pc)
			|| !wx_parse_xpm_colors(xpm, &pc)
			|| !wx_parse_xpm_pixels(xpm, &pc)
			|| pc.p != pc.e)
			return (zz_free_txt(&txt));
		zz_free_txt(&txt);
		return (wx_true);
	}
	zz_free_txt(&txt);
	return (wx_parse_xpm_error(xpm, 0, 0));
}
