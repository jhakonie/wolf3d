/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_client.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:11:35 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 14:29:18 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WC_CLIENT_H
# define WC_CLIENT_H

# include "SDL2/SDL.h"
# include "sys/socket.h"

# include "wc_draw.h"
# include "wx_frame_buffer.h"
# include "wx_net.h"
# include "wx_types.h"

/*
** 2021-03-24 todo: review the use of different size-related defines and
** variables used through out the codebase.
** - do they use consistent units?
** - are all in bytes or some other unit?
** - are variables indicating maximum size and currently used size distinct and
** consistently named?
*/

# define WC_PIPELINE_VERTICES_SIZE (65535)

struct	s_remote_server
{
	struct sockaddr	address;
	socklen_t		address_size;
	int				socket;
};
typedef struct s_remote_server	t_remote_server;

t_bool	wc_remote_server_new(t_remote_server *rs, char const *hostname,
			char const *port);
void	wc_remote_server_del(t_remote_server *rs);
t_bool	wc_remote_server_read(t_remote_server *rs, t_packet *p);
t_bool	wc_remote_server_write(t_remote_server *rs, t_client_input const *ci);

/*
** 2021-03-24 todo: review the use of t_u64 as an index type and as a buffer
** size type in the whole codebase
*/

struct	s_client
{
	t_camera			camera;
	t_pipeline_buffers	pipeline_buffers;
	t_frame_buffer		frame_buffer;
	t_client_input		input;
	t_p2				player_position;
	t_p2				other_positions[WX_SERVER_REMOTE_CLIENTS_SIZE - 1];
	t_u8				other_positions_size;
	t_remote_server		remote_server;
	SDL_Renderer		*renderer;
	t_bool				run;
	t_f64				sim_time_s;
	t_f64				sim_time_accumulator_s;
	t_f64				sim_time_step_s;
	SDL_Texture			*texture;
	t_mesh				unit_cube;
	SDL_Window			*window;
};
typedef struct s_client			t_client;

t_bool	wc_client_new(t_client *c, t_u32 window_width, t_u32 window_height);
void	wc_client_del(t_client *c);
void	wc_client_dispatch_events(t_client *c);
void	wc_client_on_expose(t_client *c);
void	wc_client_on_resize(t_client *c, t_s32 width, t_s32 height);
t_bool	wc_client_run(t_client *c);

#endif
