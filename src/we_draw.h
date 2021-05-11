/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:21:35 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 23:04:09 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WE_DRAW_H
# define WE_DRAW_H

# include "math.h"
# include "wx_math.h"
# include "wx_types.h"
# include "wx_frame_buffer.h"
# include "we_fractal.h"
# include "we_texture.h"
# include "we_ray_cast.h"
# include "wx_parse_xpm.h"
# include "stdlib.h"
# include "unistd.h"

# define WE_ID_INIT (0)
# define WE_WALL_TYPE_COUNT (2)
# define WE_TOOL_COUNT (6)
# define WE_GRID_DIVIDE (50)

/*
** 2021-03-24 todo: this is a temporary hack until something better. new
** norminette complains about any arithmetic operation in a define. this should
** be: WE_GRID_DIVIDE * WE_GRID_DIVIDE * 2
*/
# define WE_LOAD_FILE_TO_CHART_BUFFER_SIZE (5000)
# define WE_BLOCK_W (100)

# define PI (3.14159265359)
# define WE_TO_RAD (0.017453292519944)

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

typedef struct s_rgba
{
	t_u32			r;
	t_u32			g;
	t_u32			b;
	t_u32			a;
}				t_rgba;

typedef struct s_button
{
	t_p2		start;
	t_p2		end;
	t_u32		color[4];
}				t_button;

typedef struct s_grid
{
	t_p2		start;
	t_p2		end;
	t_p2		part;
	t_u32		color[2];
	t_u32		divide;
}				t_grid;

void		we_draw_pixel(t_p2 point, t_frame_buffer *fb, t_u32 color);
void		we_draw_line(t_p2 start, t_p2 end, t_frame_buffer *fb, t_u32 color);
void		we_draw_rec_full(t_p2 start, t_p2 end, t_frame_buffer *fb, t_u32 c);
void		we_draw_rec_frame(t_p2 start, t_p2 end, t_frame_buffer *fb,
				t_u32 c);
void		we_init_triangle(t_p2 a, t_p2 b, t_p2 c, t_triangle *t);
void		we_init_line(t_p2 a, t_p2 b, t_line *l);
void		we_draw_triangle(t_u32 color, t_triangle *t, t_frame_buffer *fb);
void		we_draw_grid(t_grid *g, t_frame_buffer *fb);
void		we_draw_wall(t_ray ray, t_frame_buffer *fb, t_wall_type *wall_type);
void		we_draw_texture_wall(t_ray ray, t_p2 draw, t_frame_buffer *fb,
				t_tex tex);
void		we_draw_floor(t_ray ray, t_frame_buffer *fb, t_bool draw_3d);
t_p2		we_floor_draw_end(t_ray ray);
t_tex		we_fractal_texture_create(t_p2 ray_start,
				t_s32 (*f)(t_s32, t_s32, t_fractal *), t_u32 id);

#endif
