/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_ray_cast.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 22:38:37 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/14 21:15:12 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WE_RAY_CAST_H
# define WE_RAY_CAST_H

# include "wx_types.h"
# include "wx_math.h"
# include "wx_frame_buffer.h"

struct			s_item
{
	t_p2		block;
	t_u32		id;
};
typedef struct s_item	t_item;

enum			e_side
{
	we_no_wall,
	we_horisontal,
	we_vertical
};
typedef enum e_side		t_side;

enum			e_compass
{
	we_north = 0,
	we_east = 1,
	we_south = 2,
	we_west = 3
};
typedef enum e_compass	t_compass;

struct			s_found
{
	t_p2		end;
	t_f32		distance;
	t_f32		projected_height;
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
	t_f32		player_height;
	t_f32		dist_to_screen;
	t_f32		max_distance_w;
	t_p2		start;
	t_found		wall;
};
typedef struct s_ray	t_ray;

void		we_ray_init(t_ray *ray, t_f32 player_fov_d, t_f32 screen_width,
				t_p2 player_position);
void		we_ray_calculate(t_ray *ray, t_f32 ang_ray_start_d,
				t_f32 player_direction_d);
void		we_ray_cast(t_ray *ray, t_item *chart, t_frame_buffer *fb,
				t_bool draw_3d);
t_compass	we_wall_compass_direction(t_f32 angle_ray_d, t_u32 side);
void		we_shade_pixel( t_u32 *color, t_ray ray, t_f32 distance,
				t_f32 darkness);

#endif
