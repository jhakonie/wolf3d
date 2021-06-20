/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_ray_cast.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 22:38:37 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/20 14:24:36 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WX_RAY_CAST_H
# define WX_RAY_CAST_H

# include "wx_types.h"
# include "wx_math.h"
# include "wx_frame_buffer.h"

# define WX_RAY_CAST_BUFF_SIZE_M (81)
# define WE_WALL (1)
# define WE_DOOR (2)

enum						e_side
{
	we_no_wall,
	we_horisontal,
	we_vertical
};
typedef enum e_side			t_side;

enum						e_compass
{
	we_north = 0,
	we_east = 1,
	we_south = 2,
	we_west = 3
};
typedef enum e_compass		t_compass;

struct			s_hit
{
	t_p2		hit;
	t_f32		distance;
	t_f32		projected_height;
	t_u32		tiles_id;
	t_u32		tiles_index;
	t_side		side;
	t_compass	compass;
};
typedef struct s_hit		t_hit;

struct			s_ray
{
	t_u32		nb;
	t_f32		k;
	t_f32		b;
	t_p2		step_w;
	t_f32		half_fov_d;
	t_f32		angle_d;
	t_f32		angle_to_player_d;
	t_f32		angle_increment_d;
	t_f32		player_direction_d;
	t_f32		view_height;
	t_f32		dist_to_screen_w;
	t_f32		world_end_w;
	t_p2		start;
	t_u32		tile_type_to_find;
	t_hit		tile;
	t_hit		tiles_h[WX_RAY_CAST_BUFF_SIZE_M];
	t_u32		tiles_h_size;
	t_hit		tiles_v[WX_RAY_CAST_BUFF_SIZE_M];
	t_u32		tiles_v_size;
};
typedef struct s_ray		t_ray;

void		wx_ray_init(t_ray *ray, t_f32 player_fov_d, t_f32 screen_width,
				t_p2 player_position);
void		wx_ray_calculate(t_ray *ray, t_f32 ang_ray_start_d,
				t_f32 player_direction_d);
void		wx_ray_cast(t_ray *ray, t_u32 *tiles);
t_hit		wx_ray_cast_sky(t_ray *ray);
t_compass	wx_wall_compass_direction(t_f32 angle_ray_d, t_u32 side);
void		wx_shade_pixel( t_u32 *color, t_f32 distance);

#endif
