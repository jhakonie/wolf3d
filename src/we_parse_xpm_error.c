/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_parse_xpm_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:57:53 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 22:53:56 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_parse_xpm.h"

t_bool	we_parse_xpm_error(t_xpm *xpm, t_u32 error, t_u32 index)
{
	t_u32	i;

	if (error == WE_XPM_FREE_KEY)
		free(xpm->key);
	else if (error == WE_XPM_FREE_KEYWORD)
	{
		i = 0;
		while (i < index + 1)
		{
			free(xpm->key[i].keyword);
			i++;
		}
		free(xpm->key);
	}
	else if (error == WE_XPM_FREE_PIXELS)
	{
		free(xpm->pixels);
		return (we_parse_xpm_error(xpm, WE_XPM_FREE_KEYWORD,
				xpm->color_count - 1));
	}
	return (wx_false);
}
