/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 23:38:47 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/02/18 21:13:10 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WC_DRAW_H
# define WC_DRAW_H

# include "wx_frame_buffer.h"
# include "wx_math.h"

typedef struct s_client	t_client;

struct	s_rectangle
{
	t_v2	p0;
	t_v2	p1;
};
typedef struct s_rectangle	t_rectangle;

void	wc_draw_clear(t_frame_buffer *fb);
void	wc_draw_copy(t_client *c, t_frame_buffer const *fb);
void	wc_draw_pixel(t_frame_buffer *fb, t_f32 x, t_f32 y, t_u32 abgr);
void	wc_draw_rectangle_outline(t_frame_buffer *fb, t_rectangle r);
void	wc_draw_rectangle_solid(t_frame_buffer *fb, t_rectangle r);

#endif
