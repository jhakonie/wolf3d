/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_chart_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:41:57 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/24 15:01:15 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_editor.h"
#include "stdlib.h"

/*
** 2021-03-24 todo: remove? seems unused
*/
void	we_chart_del(t_item *c)
{
	free(c);
	c = WX_NULL;
}
