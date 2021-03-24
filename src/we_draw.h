/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:21:35 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/24 16:05:29 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WE_DRAW_H
# define WE_DRAW_H

# include "math.h"
# include "wx_math.h"
# include "wx_types.h"
# include "wx_frame_buffer.h"

# define WE_ID_INIT 0
# define WE_TOOL_COUNT 6
# define WE_GRID_DIVIDE 11
/*
** 2021-03-24 todo: this is a temporary hack until something better. new
** norminette complains about any arithmetic operation in a define. this should
** be: WE_GRID_DIVIDE * WE_GRID_DIVIDE * 2
*/
# define WE_SAVE_FILE_TO_CHART_BUFFER_SIZE (242)
# define WE_BLOCK_W 100

# define PI 3.14159265359
# define WE_TO_RAD 0.017453292519944

enum			e_side
{
	we_no_wall,
	we_horisontal,
	we_vertical
};
typedef enum e_side		t_side;

enum			e_compass
{
	we_north,
	we_south,
	we_east,
	we_west
};
typedef enum e_compass	t_compass;

struct			s_item
{
	t_p2		block;
	t_u32		id;
};
typedef struct s_item	t_item;

struct			s_player
{
	t_p2		position;
	t_f32		direction_d;
	t_f32		fov_d;
	t_p2		w_start;
	t_p2		w_end;
	t_u32		w_block_count;
	t_u32		w_step;
};
typedef struct s_player	t_player;

struct			s_found
{
	t_p2		end;
	t_f32		distance;
	t_u32		chart_id;
	t_u32		chart_index;
	t_side		side;
	t_compass	compass;
};
typedef struct s_found	t_found;

struct			s_ray
{
	t_u32		nb;
	t_f32		k;
	t_f32		b;
	t_p2		delta;
	t_f32		half_fov_d;
	t_f32		angle_d;
	t_f32		angle_to_player_d;
	t_f32		angle_increment_d;
	t_f32		player_direction_d;
	t_f32		dist_to_screen;
	t_p2		start;
	t_found		wall;
};
typedef struct s_ray	t_ray;

struct			s_button
{
	t_p2		start;
	t_p2		end;
	t_u32		color[4];
};
typedef struct s_button	t_button;

struct			s_grid
{
	t_p2		start;
	t_p2		end;
	t_p2		part;
	t_u32		color[2];
	t_u32		divide;
};
typedef struct s_grid	t_grid;

void	we_draw_pixel(t_p2 point, t_frame_buffer *fb, t_u32 color);
void	we_draw_line(t_p2 start, t_p2 end, t_frame_buffer *fb, t_u32 color);
void	we_draw_rec_full(t_p2 start, t_p2 end, t_frame_buffer *fb, t_u32 c);
void	we_draw_grid(t_grid *g, t_frame_buffer *fb);
void	we_draw_rec_frame(t_p2 start, t_p2 end, t_frame_buffer *fb, t_u32 c);
void	we_ray_init(t_ray *ray, t_f32 player_fov_d, t_f32 screen_width,
			t_p2 player_position);
void	we_ray_calculate(t_ray *ray, t_f32 ang_ray_start_d,
			t_f32 player_direction_d);
void	we_ray_cast(t_ray *ray, t_item *chart);

#endif
