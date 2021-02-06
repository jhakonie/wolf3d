/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_editor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:16:44 by jhakonie          #+#    #+#             */
/*   Updated: 2021/02/03 23:01:02 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WE_EDITOR_H
# define WE_EDITOR_H

# include "SDL2/SDL.h"
# include "wx_types.h"
# include "we_draw.h"
# include "wx_frame_buffer.h"
# define WIN_H 512
# define WIN_W 512

struct				s_tool
{
	t_button		button;
	t_bool			pre_selected;
	t_bool			selected;
};
typedef struct s_tool	t_tool;

struct				s_editor
{
	SDL_Event		event;
	SDL_Window		*window;
	SDL_Texture		*texture;
	SDL_Renderer	*renderer;
	t_frame_buffer	frame_buffer;
	t_bool			quit;
	t_bool			draw;
	t_tool			tool;
};
typedef struct s_editor	t_editor;

t_bool				we_editor_new(t_editor *e, t_u32 window_width,
t_u32 window_height);
t_bool				we_editor_run(t_editor *e);
void				we_editor_del(t_editor *e);
void				we_editor_on_resize(t_editor *e, t_s32 width, t_s32 height);
void				we_draw_button(t_editor *e);

#endif
