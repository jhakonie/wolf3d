/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:21:35 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/09 02:23:04 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WE_DRAW_H
# define WE_DRAW_H

# include "SDL2/SDL.h"
# include "we_editor.h"
# include "wx_types.h"
# include "wx_frame_buffer.h"

# define WE_WIN_H 512
# define WE_WIN_W 512
# define WE_GRID_DIVIDE 22

struct		s_point
{
	t_u32	x;
	t_u32	y;
};
typedef struct s_point	t_point;

struct		s_rgba
{
	t_u8	a;
	t_u8	b;
	t_u8	g;
	t_u8	r;
};
typedef struct s_rgba	t_rgba;

struct		s_button
{
	t_point	start;
	t_point	end;
	t_rgba	color[4];
};
typedef struct s_button	t_button;

struct		s_grid
{
	t_point	start;
	t_point	end;
	t_point part;
	t_rgba	color[2];
	t_u32	divide;
};
typedef struct s_grid	t_grid;

void		we_u32_to_rgba(t_rgba *color, t_u32 color_int);
void		we_draw_pixel(t_point point, t_frame_buffer *fb, t_rgba color);
void		we_draw_line(t_point start, t_point end, t_frame_buffer *fb,
				t_rgba color);
void		we_draw_rec_full(t_point start, t_point end, t_frame_buffer *fb,
				t_rgba c);
void		we_draw_grid(t_grid *g, t_frame_buffer *fb);
void		we_draw_rec_frame(t_point start, t_point end, t_frame_buffer *fb,
				t_rgba c);

#endif
