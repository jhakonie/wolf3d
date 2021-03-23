/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_editor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:16:44 by jhakonie          #+#    #+#             */
/*   Updated: 2021/03/23 18:55:43 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WE_EDITOR_H
# define WE_EDITOR_H

# include "SDL2/SDL.h"
# include "wx_types.h"
# include "we_draw.h"
# include "wx_frame_buffer.h"
# include "unistd.h"
# define WE_WIN_H 512
# define WE_WIN_W 512

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

struct				s_map
{
	char			*file;
	t_grid			grid;
	t_item			*chart;
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
void				we_editor_on_resize(t_editor *e, t_s32 width, t_s32 height);
void				we_init_tools(t_tools *t, t_u32 win_w, t_u32 win_h);
void				we_init_wall(t_tool *t, t_u32 win_w, t_u32 win_h);
void				we_init_floor(t_tool *t, t_u32 win_w, t_u32 win_h);
void				we_init_player_location(t_tool *t,
						t_u32 win_w, t_u32 win_h);
void				we_init_empty(t_tool *t, t_u32 win_w, t_u32 win_h);
void				we_init_save(t_tool *t, t_u32 win_w, t_u32 win_h);
void				we_init_map(t_map *m, t_u32 win_w, t_u32 win_h);
void				we_init_chart(t_map *m);
void				we_init_player(t_player *p, t_map *m);
t_p2				we_from_win_to_map(t_p2 win, t_map m);
t_p2				we_from_map_to_win(t_p2 map, t_map m);
void				we_save_win_to_map(t_p2 win, t_editor *e);
void				we_save_map_to_file(t_editor *e);
t_bool				we_pos_mouse_tool(t_tool *t, t_u32 *draw, t_u32 x, t_u32 y);
void				we_pos_mouse_grid(t_editor *e, t_u32 x, t_u32 y);
void				we_pos_on_click_tool(t_editor *e, t_u32 x, t_u32 y);
void				we_pos_on_click_grid(t_editor *e, t_u32 x, t_u32 y);
void				we_mouse_button_up(t_bool *ptr_hold, int button);
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

#endif
