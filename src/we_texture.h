/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_texture.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 22:24:54 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/27 22:14:32 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WE_TEXTURE_H
# define WE_TEXTURE_H

# include "wx_frame_buffer.h"
# include "wx_math.h"
# include "wx_parse_xpm.h"

typedef struct s_texture_index
{
	t_p2	coord;
	t_f32	increment_y;
	t_p2	increment;
	t_u32	index;

}	t_texture_index;

typedef struct s_tex
{
	t_u32	height;
	t_u32	width;
	t_u32	fractal[2500];
	t_u64	size;
	t_u32	*texture;
}	t_tex;

typedef struct s_wall_type
{
	t_tex	wall[4];
}	t_wall_type;

t_bool		we_texture_new(char *filename, t_tex *t);

#endif
