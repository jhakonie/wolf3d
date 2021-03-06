/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 23:38:47 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/06 14:51:18 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WC_DRAW_H
# define WC_DRAW_H

# include "wx_frame_buffer.h"
# include "wx_math.h"

typedef struct s_client	t_client;

struct	s_camera
{
	t_q4	orientation;
	t_p3	position;
	t_f32	hfov_rad;
	t_f32	aspect_ratio;
	t_f32	near;
	t_f32	far;
};
typedef struct s_camera	t_camera;

struct	s_rectangle
{
	t_p2	p0;
	t_p2	p1;
};
typedef struct s_rectangle	t_rectangle;

struct	s_draw_context
{
	t_m44	clip_from_view;
	t_m44	ndc_from_clip;
	t_q4	object_orientation;
	t_p3	object_position;
	t_m44	view_from_world;
	t_m44	window_from_ndc;
	t_m44	world_from_object;
};
typedef struct s_draw_context	t_draw_context;

void	wc_draw(t_client *c);
void	wc_draw_clear(t_frame_buffer *fb);
void	wc_draw_copy(t_client *c, t_frame_buffer const *fb);
void	wc_draw_pixel(t_frame_buffer *fb, t_f32 x, t_f32 y, t_u32 abgr);
void	wc_draw_rectangle_outline(t_frame_buffer *fb, t_p3 p, t_f32 width,
	t_u32 abgr);
void	wc_draw_rectangle_solid(t_frame_buffer *fb, t_p3 p, t_f32 width,
	t_u32 abgr);

#endif
