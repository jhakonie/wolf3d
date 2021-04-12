/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_parse_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:39:38 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 22:51:59 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "we_draw.h"

static void	zz_calculate_hex(t_u32	*number, t_u32 *hex)
{
	t_rgba	num_part;

	num_part.r = number[0] * 16 + number[1];
	num_part.g = number[2] * 16 + number[3];
	num_part.b = number[4] * 16 + number[5];
	num_part.a = number[6] * 16 + number[7];
	*hex = (num_part.a << 24) | (num_part.r << 16)
		| (num_part.g << 8) | (num_part.b << 0);
}

t_bool	we_parse_hexa(t_u8 *str, t_u32 *hex, t_u32 len)
{
	t_u32	number[8];
	t_u32	i;

	i = 0;
	if (!str || !hex || len > 8)
		return (wx_false);
	wx_buffer_set(number, sizeof(t_u32) * 8, 0);
	while (i < len)
	{
		if (str[i] >= '0' && str[i] <= '9')
			number[i] = (str[i] - '0');
		else if (str[i] >= 'A' && str[i] <= 'F')
			number[i] = (str[i] - 55);
		else if (str[i] >= 'a' && str[i] <= 'f')
			number[i] = (str[i] - 87);
		else
			return (wx_false);
		i++;
	}
	zz_calculate_hex(number, hex);
	return (wx_true);
}
