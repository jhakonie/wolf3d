/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_parse_xpm_comment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 22:11:24 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 23:56:20 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_parse_xpm.h"

t_bool	we_parse_xpm_comment(t_parse_context *pc)
{
	if (wx_parse_keyword(pc, "/*")
		&& we_parse_until(pc, '*')
		&& wx_parse_keyword(pc, "/")
		&& wx_parse_whitespace(pc))
		return (wx_true);
	return (wx_false);
}
