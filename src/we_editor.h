/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_editor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:16:44 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/15 00:48:15 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WE_EDITOR_H
# define WE_EDITOR_H

# include "SDL2/SDL.h"
# include "we_draw.h"
# include "unistd.h"
# define WE_WIN_H (512)
# define WE_WIN_W (512)

struct				s_tool
{
	t_button		button;
	t_bool			pre_selected;
	t_bool			selected;
};
typedef struct s_tool	t_tool;

struct				s_tools
{
	t_p2			start;
	t_p2			end;
	t_u32			color[2];
	t_u32			id;
	t_tool			tool[6];
};
typedef struct s_tools	t_tools;

struct			s_player
{
	t_f32		height;
	t_p2		position;
	t_f32		direction_d;
	t_f32		dist_to_screen;
	t_f32		fov_d;
	t_p2		w_start;
	t_p2		w_end;
	t_u32		w_block_count;
	t_f32		w_step;
	t_bool		run;
	t_bool		wall_collision;
};
typedef struct s_player	t_player;

struct				s_map
{
	char			*file;
	t_grid			grid;
	t_item			*chart;
	t_wall_type		wall_type[WE_WALL_TYPE_COUNT];
	t_u32			block_count;
	t_p2			player_pos_chart;
	t_p2			player_pos_chart_old;
	t_u32			player_pos_old_id;
	t_p2			ptr;
	t_bool			ptr_draw;
	t_bool			ptr_clear;
	t_bool			ptr_hold;
	t_bool			draw_3d;
	t_bool			draw_rays;
	t_bool			draw_rays_wall;
	t_bool			draw_rays_no_wall;
};
typedef struct s_map	t_map;

struct				s_editor
{
	SDL_Event		event;
	SDL_Window		*window;
	SDL_Texture		*texture;
	SDL_Renderer	*renderer;
	t_frame_buffer	frame_buffer;
	t_bool			quit;
	t_bool			draw;
	t_tools			tools;
	t_map			map;
	t_player		player;
};
typedef struct s_editor	t_editor;

t_bool				we_editor_new(t_editor *e, t_u32 window_width,
						t_u32 window_height);
t_bool				we_editor_run(t_editor *e);
void				we_editor_del(t_editor *e);
t_bool				we_chart_new(t_map *m);
void				we_chart_del(t_item *c);
t_bool				we_wall_type_new(t_wall_type *wall_type);
t_bool				we_wall_type_del(t_wall_type *wall_type,
						t_u32 wall_type_index, t_u32 wall_index);
void				we_window_event(t_editor *e, SDL_WindowEvent *w);
void				we_draw_to_window(t_editor *e);
void				we_init_tools(t_tools *t, t_u32 win_w, t_u32 win_h);
void				we_init_wall(t_tool *t, t_u32 win_w, t_u32 win_h);
void				we_init_floor(t_tool *t, t_u32 win_w, t_u32 win_h);
void				we_init_player_location(t_tool *t,
						t_u32 win_w, t_u32 win_h);
void				we_init_empty(t_tool *t, t_u32 win_w, t_u32 win_h);
void				we_init_save(t_tool *t, t_u32 win_w, t_u32 win_h);
void				we_init_map(t_map *m, t_u32 win_w, t_u32 win_h);
t_bool				we_init_textures(t_wall_type *wall_type);
void				we_init_chart(t_map *m);
void				we_init_player(t_player *p, t_map *m, t_u32 screen_width);
t_p2				we_from_win_to_map(t_p2 win, t_map m);
t_p2				we_from_map_to_win(t_p2 map, t_map m);
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
void				we_draw_rays(t_ray ray, t_map map, t_frame_buffer *fb);
void				we_draw_3d(t_frame_buffer *frame_buffer, t_player player,
						t_map map);
t_f32				we_to_rad(t_f32 deg);
void				we_player_move(t_u32 key, t_editor *e);
void				we_player_rotate(t_editor *e, t_u32 x, t_u32 y);

#endif
