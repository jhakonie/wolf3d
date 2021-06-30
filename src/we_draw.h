/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:21:35 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/30 14:03:27 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WE_DRAW_H
# define WE_DRAW_H

# include "math.h"
# include "wx_draw.h"
# include "wx_parse_xpm.h"
# include "stdlib.h"
# include "unistd.h"

# define WE_ID_INIT (0)
# define WE_TOOL_COUNT (6)

typedef struct s_line
{
	t_p2	start;
	t_p2	end;
	t_p2	delta;
	t_f32	k;
	t_f32	b;
}				t_line;

enum			e_order_3
{
	we_max = 0,
	we_mid = 1,
	we_min = 2
};
typedef enum e_order		t_order_3;

typedef struct s_triangle
{
	t_p2	a;
	t_p2	b;
	t_p2	c;
	t_line	min_mid;
	t_line	min_max;
	t_line	mid_max;
	t_p2	points[3];
	t_u32	color;
}					t_triangle;

typedef struct s_button
{
	t_p2		start;
	t_p2		end;
	t_texture	icon;
}				t_button;

typedef struct s_grid
{
	t_p2		start;
	t_p2		end;
	t_p2		part;
	t_u32		color[2];
	t_u32		divide;
}				t_grid;

void		we_draw_line(t_p2 start, t_p2 end, t_frame_buffer *fb, t_u32 color);
void		we_draw_clip(t_p2 *p, t_frame_buffer *fb);
void		we_draw_rec_texture(t_p2 start, t_p2 end,
				t_frame_buffer *fb, t_texture *t);
void		we_draw_rec_full(t_p2 start, t_p2 end, t_frame_buffer *fb, t_u32 c);
void		we_draw_rec_frame(t_p2 start, t_p2 end, t_frame_buffer *fb,
				t_u32 c);
void		we_init_triangle(t_p2 a, t_p2 b, t_p2 c, t_triangle *t);
void		we_init_line(t_p2 a, t_p2 b, t_line *l);
void		we_draw_triangle(t_u32 color, t_triangle *t, t_frame_buffer *fb);
void		we_draw_grid(t_grid *g, t_frame_buffer *fb);

#endif
