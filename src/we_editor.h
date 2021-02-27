/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_editor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:16:44 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/27 13:33:42 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WE_EDITOR_H
# define WE_EDITOR_H

# include "../build/libsdl2/include/SDL2/SDL.h"
# include "wx_types.h"
# include "we_draw.h"
# include "wx_frame_buffer.h"
# include <stdio.h>
# include <unistd.h>
# define WE_WIN_H 512
# define WE_WIN_W 512
# define WE_ID_INIT 0
# define WE_TOOL_COUNT 5
# define WE_GRID_DIVIDE 64

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
	t_rgba			color[2];
	t_u32			id;
	t_tool			tool[5];
};
typedef struct s_tools	t_tools;

struct				s_item
{
	t_p2			block;
	t_u32			id;
};
typedef struct s_item	t_item;

struct				s_map
{
	char			*file;
	t_grid			grid;
	t_item			*chart;
	t_u32			block_count;
	t_p2			ptr;
	t_bool			ptr_draw;
	t_bool			ptr_clear;
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
void				we_init_door(t_tool *t, t_u32 win_w, t_u32 win_h);
void				we_init_save(t_tool *t, t_u32 win_w, t_u32 win_h);
void				we_init_map(t_map *m, t_u32 win_w, t_u32 win_h);
void				we_init_chart(t_map *m);
t_p2				we_from_win_to_map(t_p2 win, t_editor *e);
t_p2				we_from_map_to_win(t_p2 map, t_editor *e);
void				we_save_win_to_map(t_p2 win, t_editor *e);
void				we_save_map_to_file(t_editor *e);
t_bool				we_pos_mouse_tool(t_tool *t, t_u32 *draw, t_u32 x, t_u32 y);
void				we_pos_mouse_grid(t_map *m, t_u32 *draw, t_u32 x, t_u32 y);
void				we_pos_on_click_tool(t_editor *e, t_u32 x, t_u32 y);
void				we_pos_on_click_grid(t_editor *e, t_u32 x, t_u32 y);
void				we_draw(t_editor *e);
void				we_draw_toolbar(t_editor *e);
void				we_draw_button(t_tool *t, t_frame_buffer *fb);
void				we_draw_grid(t_grid *g, t_frame_buffer *data);
void				we_draw_block(t_editor *e, t_u32 id);
void				we_draw_map(t_editor *e);

#endif
