/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_xpm_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:56:33 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/10 19:59:19 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

void	we_xpm_del(t_xpm *xpm)
{
	we_parse_xpm_error(xpm, WE_XPM_FREE_PIXELS, xpm->color_count - 1);
}
