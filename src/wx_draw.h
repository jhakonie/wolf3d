#ifndef WX_DRAW_H
# define WX_DRAW_H

# include "wx_types.h"
# include "wx_math.h"
# include "wx_ray_cast.h"
# include "wx_frame_buffer.h"
/*
** REMEMBER to update WX_MAP_READ_BUFF_SIZE
** (2 * WX_MAP_TILES_WIDTH * WX_MAP_TILES_WIDTH)
** and WX_MAP_SIZE (WX_MAP_TILES_WIDTH * WX_MAP_TILES_WIDTH),
** used for reading map.
** and WX_RAY_CAST_BUFF_SIZE_M in wx_raycast.h, used for ray cast buffer.
** ----> sqrt(WX_MAP_SIZE + WX_MAP_SIZE);
** IF WX_MAP_TILES_WIDTH is altered!
*/
# define WX_MAP_TILES_WIDTH (57)

/*
** 2021-03-24 todo: this is a temporary hack until something better. new
** norminette complains about any arithmetic operation in a define. this should
** be: WX_MAP_TILES_WIDTH * WX_MAP_TILES_WIDTH * 2
*/
# define WX_MAP_READ_BUFF_SIZE (6498)
# define WX_MAP_SIZE (3249)
# define WX_TILE_WIDTH (2)

# define WX_MAP_TILE_TYPE_FLOOR (0)
# define WX_MAP_TILE_TYPE_DOOR (2)
# define WX_MAP_TILE_TYPE_PLAYER_SPAWN (3)
# define WX_MAP_TILE_TYPE_WALL (1)

typedef struct s_rgba
{
	t_u8			r;
	t_u8			g;
	t_u8			b;
	t_u8			a;
}				t_rgba;

struct			s_draw_floor
{
	t_p2		end_w;
	t_p2		delta_w;
	t_f32		end_distance_w;
	t_p2		start_fb;
	t_p2		end_fb;
};
typedef struct s_draw_floor	t_draw_floor;

struct	s_texture
{
	t_u8	*buffer;
	t_u64	buffer_size;
	t_u32	width;
	t_u32	height;
};
typedef struct s_texture	t_texture;

typedef struct s_map_textures
{
	t_texture	walls[4];
	t_texture	floor;
	t_texture	skys[4];
	t_texture	door;
}	t_map_textures;

typedef struct s_texture_index
{
	t_p2	coord;
	t_f32	increment_y;
	t_p2	increment;
	t_u32	index;
	t_u32	max_index;

}	t_texture_index;

struct				s_move
{
	t_p2		forward;
	t_p2		backward;
	t_p2		left;
	t_p2		right;
};
typedef struct s_move		t_move;

struct			s_player
{
	t_f32		height;
	t_p2		position;
	t_f32		direction_d;
	t_f32		dist_to_screen_w;
	t_f32		fov_d;
	t_u32		w_tile_count;
	t_f32		w_step;
	t_bool		run;
	t_move		move;
	t_bool		wall_collision;
};
typedef struct s_player		t_player;

struct	s_map
{
	t_u32			tiles[WX_MAP_SIZE];
	t_u64			width;
	t_u64			height;
	t_f32			tile_width;
	t_f32			wall_height;
	t_map_textures	textures;
};
typedef struct s_map		t_map;

void		wx_draw_pixel(t_p2 point, t_frame_buffer *fb, t_u32 color);
void		wx_draw_3d(t_frame_buffer *frame_buffer, t_player player,
				t_map *m);
void		wx_draw_wall(t_ray ray, t_frame_buffer *fb,
				t_map_textures *textures);
void		wx_draw_wall_texture(t_ray *ray, t_p2 draw, t_frame_buffer *fb,
				t_texture *tex);
void		wx_draw_floor(t_ray ray, t_frame_buffer *fb,
				t_texture *texture);
t_p2		wx_draw_floor_tile_end(t_ray *ray);
void		wx_draw_floor_player_position(t_frame_buffer *fb, t_ray *ray,
				t_texture *t);
void		wx_draw_sky(t_frame_buffer *fb, t_ray ray, t_texture *skys);
void		wx_draw_door(t_ray ray, t_frame_buffer *fb,
				t_map_textures *textures);
void		wx_draw_door_distance(t_ray *ray);

#endif
