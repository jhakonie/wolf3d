/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_parse_xpm_pixels.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 01:08:09 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 23:00:00 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_parse_xpm.h"

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
			return (we_parse_xpm_error(xpm,
					WE_XPM_FREE_PIXELS, xpm->color_count - 1));
	}
	else
	{
		if (!wx_parse_keyword(pc, "\""))
			return (we_parse_xpm_error(xpm,
					WE_XPM_FREE_PIXELS, xpm->color_count - 1));
		wx_parse_whitespace(pc);
		if (!wx_parse_keyword(pc, "};"))
			return (we_parse_xpm_error(xpm,
					WE_XPM_FREE_PIXELS, xpm->color_count - 1));
		wx_parse_whitespace(pc);
	}
	return (wx_true);
}

static t_bool	zz_is_key(t_parse_context *pc, t_xpm *xpm,
t_parse_xpm_index i)
{
	t_u32		keyword_index;

	keyword_index = 0;
	while (*pc->p == xpm->key[i.key_index].keyword[keyword_index]
		&& keyword_index < xpm->keyword_length
		&& pc->p != pc->e)
	{
		if (keyword_index == xpm->keyword_length - 1)
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
** If no keyword matching the key is found, free saved colors and
** previously allocated pixel-array.
*/

static t_bool	zz_key_match(t_parse_context *pc, t_xpm *xpm,
	t_parse_xpm_index i)
{
	t_u32		color;

	i.key_index = 0;
	while (i.key_index < xpm->color_count)
	{
		if (zz_is_key(pc, xpm, i))
		{
			color = xpm->key[i.key_index].color;
			xpm->pixels[i.pixel_index] = color;
			return (wx_true);
		}
		i.key_index++;
	}
	return (we_parse_xpm_error(xpm,
			WE_XPM_FREE_PIXELS, xpm->color_count - 1));
}

/*
** Parse comment, allocate pixel-array. Free saved colors upon failure.
** Loop through xpm image comparing pixel keys to color keywords.
** Free saved colors and previously allocated pixel-array upon failure.
*/

t_bool	we_parse_xpm_pixels(t_xpm *xpm, t_parse_context *pc)
{
	t_u32				size;
	t_parse_xpm_index	i;

	size = xpm->height * xpm->width * sizeof(t_u32);
	xpm->pixels = (t_u32 *)malloc(size);
	if (!wx_parse_keyword(pc, "\"") || !xpm->pixels)
		return (we_parse_xpm_error(xpm,
				WE_XPM_FREE_KEYWORD, (xpm->color_count - 1)));
	i.pixel_index = 0;
	i.h = 0;
	while (i.h < xpm->height)
	{
		i.w = 0;
		while (i.w < xpm->width && pc->p != pc->e)
		{
			if (!zz_key_match(pc, xpm, i))
				return (wx_false);
			i.pixel_index++;
			i.w++;
		}
		if (!zz_parse_end_of_line(pc, i, xpm))
			return (wx_false);
		i.h++;
	}
	return (wx_true);
}
