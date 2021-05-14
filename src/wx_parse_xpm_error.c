/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_parse_xpm_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:57:53 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/14 15:57:55 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wx_parse_xpm.h"

t_bool	wx_parse_xpm_error(t_xpm *xpm, t_u32 error,
	char *error_message, t_u32 len)
{
	if (error == WX_XPM_FREE_TABLE)
		free(xpm->table);
	else if (error == WX_XPM_FREE_PIXELS)
	{
		free(xpm->table);
		free(xpm->pixels);
	}
	write(1, error_message, len);
	return (wx_false);
}
