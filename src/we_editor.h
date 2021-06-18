/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_editor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:16:44 by jhakonie          #+#    #+#             */
/*   Updated: 2021/06/19 00:40:49 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WE_EDITOR_H
# define WE_EDITOR_H

# include "SDL2/SDL.h"
# include "we_draw.h"
# include "wx_path.h"
# include "wx_draw.h"
# include "unistd.h"
# define WE_WIN_H (512)
# define WE_WIN_W (512)
# define WE_RESOURCES_COUNT (8)

struct				s_tool
{
	t_button		button;
	t_bool			pre_selected;
	t_bool			selected;
};
typedef struct s_tool	t_tool;

struct				s_toolbar
{
	t_p2			start;
	t_p2			end;
	t_u32			color[2];
	t_u32			id;
	t_tool			tool[WE_TOOL_COUNT];
}	t_toolbar;

struct			s_time
{
	t_f64			sim_time_s;
	t_f64			sim_time_accumulator_s;
	t_f64			sim_time_step_s;
};
typedef struct s_time	t_time;

struct				s_level
{
	t_c8		*name;
	t_path		paths[WE_RESOURCES_COUNT];
	t_map		map;
};
typedef struct s_level	t_level;

struct				s_map_view
{
	t_grid			grid;
	t_u32			tile_count;
	t_p2			player_pos_tiles;
	t_p2			player_pos_tiles_old;
	t_u32			player_pos_old_id;
	t_p2			ptr;
	t_bool			ptr_draw;
	t_bool			ptr_clear;
	t_bool			ptr_hold;
	t_bool			draw_3d;
	t_bool			draw_rays;
}	t_map_view;

struct				s_editor
{
	SDL_Event		event;
	SDL_Window		*window;
	SDL_Texture		*texture;
	SDL_Renderer	*renderer;
	t_frame_buffer	frame_buffer;
	t_bool			quit;
	t_bool			draw;
	t_toolbar		tools;
	t_map_view		map_view;
	t_level			level;
	t_player		player;
	t_time			time;
};
typedef struct s_editor	t_editor;

t_bool				we_editor_new(t_editor *e, t_u32 window_width,
						t_u32 window_height);
t_bool				we_editor_run(t_editor *e);
void				we_editor_del(t_editor *e);
t_bool				we_textures_new(t_map_textures *textures,
						t_path *paths);
t_bool				we_texture_new(char *filename, t_texture *t);
t_bool				we_textures_del(t_map_textures *textures);
void				we_window_event(t_editor *e, SDL_WindowEvent *w);
void				we_draw_to_window(t_editor *e);
void				we_init_toolbar(t_toolbar *t, t_u32 win_w, t_u32 win_h);
void				we_init_wall(t_tool *t, t_u32 win_w, t_u32 win_h);
void				we_init_door(t_tool *t, t_u32 win_w, t_u32 win_h);
void				we_init_player_location(t_tool *t,
						t_u32 win_w, t_u32 win_h);
void				we_init_empty(t_tool *t, t_u32 win_w, t_u32 win_h);
void				we_init_save(t_tool *t, t_u32 win_w, t_u32 win_h);
t_bool				we_toolbar_icons_new(t_tool *t);
t_bool				we_toolbar_icons_del(t_tool *t);
void				we_init_map(t_map_view *m, t_u32 win_w, t_u32 win_h);
t_bool				we_level_new(t_level *l);
void				we_level_del(t_level *l);
t_bool				we_paths_new(t_path *p, t_c8 *level);
t_bool				we_paths_del(t_path *p, t_u32 size);
t_bool				wx_path_new3(t_path	*p, t_c8 const *start,
						t_c8 const *middle, t_c8 const *end);
void				we_init_tiles(t_level *l);
void				we_tiles_set(t_map *m);
void				we_init_player(t_player *p, t_map *map, t_map_view *m,
						t_u32 screen_width);
t_p2				we_from_win_to_map(t_p2 win, t_map_view m);
t_p2				we_from_map_to_win(t_p2 map, t_map_view m);
void				we_save_win_to_map(t_p2 win, t_editor *e);
void				we_save_map_to_file(t_editor *e);
void				we_mouse_event(t_editor *e);
void				we_mouse_pos_grid(t_editor *e, t_u32 x, t_u32 y);
t_bool				we_mouse_pos_tool(t_tool *t, t_u32 *draw, t_u32 x, t_u32 y);
void				we_mouse_pos_tool_on_click(t_editor *e, t_u32 x, t_u32 y);
void				we_mouse_pos_grid_on_click(t_editor *e, t_u32 x, t_u32 y);
void				we_key_event(t_u32 key, t_editor *e);
void				we_draw(t_editor *e);
void				we_draw_toolbar(t_editor *e);
void				we_draw_button(t_tool *t, t_frame_buffer *fb);
void				we_draw_grid(t_grid *g, t_frame_buffer *data);
void				we_draw_block(t_editor *e, t_u32 id);
void				we_draw_map(t_editor *e);
void				we_draw_player(t_editor *e);
void				we_draw_rays(t_ray *ray, t_map_view map,
						t_frame_buffer *fb);
t_f32				we_to_rad(t_f32 deg);
void				we_player_move(t_u32 key, t_editor *e);
void				we_player_rotate(t_editor *e, t_u32 x, t_u32 y);

#endif
