/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_client.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:11:35 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/06/18 18:50:53 by jhakonie         ###   ########.fr       */
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
	t_u64			received_packet_seq;
	t_u64			sent_packet_seq;
};
typedef struct s_remote_server	t_remote_server;

t_bool	wc_remote_server_new(t_remote_server *rs, char const *hostname,
			char const *port);
void	wc_remote_server_del(t_remote_server *rs);
t_bool	wc_remote_server_read(t_remote_server *rs, t_packet *p);
t_bool	wc_remote_server_write(t_remote_server *rs, t_client_input const *ci,
			t_q4 const *player_orientation);

/*
** 2021-03-24 todo: review the use of t_u64 as an index type and as a buffer
** size type in the whole codebase
*/

/*
** 2021-05-22 note: make sure all the subobjects behave nicely when they are
** released after just being zeroed out. to simplify implementation _new() just
** zeroes out the client object and calls _del() on failure
*/
struct	s_client
{
	void				(*draw)(struct s_client *);
	t_camera			camera;
	t_pipeline_buffers	pipeline_buffers;
	t_frame_buffer		frame_buffer;
	t_depth_buffer		depth_buffer;
	t_map_mesh			map_mesh;
	t_map				map;
	t_client_input		input;
	t_s32				mouse_x;
	t_s32				mouse_y;
	t_s32				mouse_dx;
	t_s32				mouse_dy;
	t_client_move_mode	move_mode;
	t_f64				net_time_accumulator_s;
	t_f64				net_time_step_s;
	t_q4				player_orientation;
	t_p3				player_position;
	t_q4				other_orientations[WX_SERVER_REMOTE_CLIENTS_SIZE - 1];
	t_p3				other_positions[WX_SERVER_REMOTE_CLIENTS_SIZE - 1];
	t_u8				others_size;
	t_remote_server		remote_server;
	SDL_Renderer		*renderer;
	t_bool				run;
	t_f64				sim_time_s;
	t_f64				sim_time_accumulator_s;
	t_f64				sim_time_step_s;
	SDL_Texture			*texture;
	t_mesh				test_mesh;
	t_texture			test_texture;
	SDL_Window			*window;
};
typedef struct s_client			t_client;

t_bool	wc_client_new(t_client *c, t_u32 window_width, t_u32 window_height,
			char const *map_name);
void	wc_client_del(t_client *c);
void	wc_client_dispatch_events(t_client *c);
t_bool	wc_client_load_data(t_client *c, char const *map_name);
void	wc_client_on_expose(t_client *c);
void	wc_client_on_resize(t_client *c, t_s32 width, t_s32 height);
t_bool	wc_client_run(t_client *c);

#endif
