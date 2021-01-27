/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_client.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:11:35 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/01/27 11:40:51 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WC_CLIENT_H
# define WC_CLIENT_H

# include "SDL2/SDL.h"

# include "wx_frame_buffer.h"
# include "wx_types.h"

struct	s_client
{
	t_bool			draw;
	SDL_Event		event;
	t_frame_buffer	frame_buffer;
	SDL_Renderer	*renderer;
	t_bool			run;
	SDL_Texture		*texture;
	SDL_Window		*window;
};
typedef struct s_client	t_client;

t_bool	wc_client_new(t_client *c, t_u32 window_width, t_u32 window_height);
void	wc_client_del(t_client *c);
void	wc_client_on_expose(t_client *c);
void	wc_client_on_resize(t_client *c, t_s32 width, t_s32 height);
t_bool	wc_client_run(t_client *c);

#endif
