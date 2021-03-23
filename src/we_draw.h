/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:21:35 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/23 13:14:52 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WE_DRAW_H
# define WE_DRAW_H

# include "wx_math.h"
# include "wx_types.h"
# include "wx_frame_buffer.h"

# define WE_HORIZONTAL 1
# define WE_VERTICAL 0
# define WE_NO_WALL 2

struct		s_p2i
{
	t_s32	x;
	t_s32	y;
};
typedef struct s_p2i	t_p2i;

struct		s_item
{
	t_p2	block;
	t_u32	id;
};
typedef struct s_item	t_item;

struct		s_ray_cast
{
	t_p2i	map;
	t_p2	side;
	t_p2	delta;
	t_p2i	step;
	t_u32	wall;
	t_f32	wall_dist;
};
typedef struct s_ray_cast	t_ray_cast;

struct		s_ray
{
	t_u32	nb;
	t_f32	k;
	t_f32	b;
	t_p2	delta;
	t_f32	half_fov_d;
	t_f32	angle_d;
	t_f32	angle_to_player_d;
	t_f32	angle_increment_d;
	t_f32	player_direction_d;
	t_f32	dist_to_screen;
	t_f32	dist_to_wall;
	t_p2	start;
	t_p2	end;
	t_u32	chart_index;
	t_u32	compass;
};
typedef struct s_ray	t_ray;

struct		s_button
{
	t_p2	start;
	t_p2	end;
	t_u32	color[4];
};
typedef struct s_button	t_button;

struct		s_grid
{
	t_p2	start;
	t_p2	end;
	t_p2	part;
	t_u32	color[2];
	t_u32	divide;
};
typedef struct s_grid	t_grid;

void		we_draw_pixel(t_p2 point, t_frame_buffer *fb, t_u32 color);
void		we_draw_line(t_p2 start, t_p2 end, t_frame_buffer *fb,
				t_u32 color);
void		we_draw_rec_full(t_p2 start, t_p2 end, t_frame_buffer *fb,
				t_u32 c);
void		we_draw_grid(t_grid *g, t_frame_buffer *fb);
void		we_draw_rec_frame(t_p2 start, t_p2 end, t_frame_buffer *fb,
				t_u32 c);
void		we_ray_cast(t_ray *ray, t_item *chart);
t_bool		we_ray_cast_check_map(t_item *chart, t_ray *ray, t_u32 line,
				t_u32 index);
#endif
