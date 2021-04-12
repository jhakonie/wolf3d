/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_parse_obj_context_del.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 08:50:57 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/04/12 22:01:45 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wc_parse.h"

void	wc_parse_obj_context_del(t_parse_obj_context *poc)
{
	wc_p2s_del(&poc->uvs);
	wc_p3s_del(&poc->positions);
	wc_n3s_del(&poc->normals);
	wc_obj_vertices_del(&poc->vertices);
}
