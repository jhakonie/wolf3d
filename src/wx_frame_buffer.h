/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_frame_buffer.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 10:54:39 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 15:47:12 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WX_FRAME_BUFFER_H
# define WX_FRAME_BUFFER_H

# include "wx_types.h"

struct	s_frame_buffer
{
	t_u8	*data;
	t_u64	data_size;
	t_u32	width;
	t_u32	height;
};
typedef struct s_frame_buffer	t_frame_buffer;

t_bool	wx_frame_buffer_new(t_frame_buffer *fb, t_u32 image_width,
			t_u32 image_height);
void	wx_frame_buffer_del(t_frame_buffer *fb);

#endif
