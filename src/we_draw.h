/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:21:35 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/02 11:31:35 by jhakonie         ###   ########.fr       */
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

/*
** REMEMBER to update WE_MAP_BUFF_SIZE (2 * WE_GRID_DIVIDE * WE_GRID_DIVIDE)
** and WE_MAP_SIZE (WE_GRID_DIVIDE * WE_GRID_DIVIDE), used for reading map.
** and WE_RAY_CAST_BUFF_SIZE_M in we_raycast.h, used for ray cast buffer.
** ----> sqrt(WE_MAP_SIZE + WE_MAP_SIZE);
** IF WE_GRID_DIVIDE is altered!
*/
# define WE_GRID_DIVIDE (57)

/*
** 2021-03-24 todo: this is a temporary hack until something better. new
** norminette complains about any arithmetic operation in a define. this should
** be: WE_GRID_DIVIDE * WE_GRID_DIVIDE * 2
*/
# define WE_MAP_BUFF_SIZE (6498)
# define WE_MAP_SIZE (3249)
# define WE_BLOCK_W (10)

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

struct			s_draw_floor
{
	t_p2		end_w;
	t_p2		delta_w;
	t_f32		end_distance_w;
	t_p2		start_fb;
	t_p2		end_fb;
};
typedef struct s_draw_floor	t_draw_floor;

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
				t_tex *tex);
void		we_draw_floor(t_ray ray, t_frame_buffer *fb,
				t_wall_type *wall_type);
t_p2		we_floor_draw_end(t_ray ray);
t_tex		we_fractal_texture_create(t_p2 ray_start,
				t_s32 (*f)(t_s32, t_s32, t_fractal *), t_u32 id);

#endif
