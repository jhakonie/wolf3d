# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/25 13:22:26 by jhakonie          #+#    #+#              #
#    Updated: 2021/02/21 16:47:45 by ***REMOVED***         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

src_dir = src/
build_dir = build/

libsdl2_makefile = libsdl2/Makefile
libsdl2_lib = $(build_dir)libsdl2/lib/libSDL2.a
libsdl2_cflags = `$(build_dir)libsdl2/bin/sdl2-config --cflags`
libsdl2_ldflags = `$(build_dir)libsdl2/bin/sdl2-config --libs`

client_src_files = $(addprefix $(src_dir), \
	wc_client_dispatch_events.c \
	wc_client_del.c \
	wc_client_new.c \
	wc_client_run.c \
	wc_draw_clear.c \
	wc_draw_copy.c \
	wc_draw_pixel.c \
	wc_draw_rectangle_solid.c \
	wc_draw_rectangle_outline.c \
	wc_remote_server_new.c \
	wc_remote_server_del.c \
	wc_remote_server_read.c \
	wc_remote_server_write.c \
	wc_main.c \
	wx_address_equal.c \
	wx_buffer_copy.c \
	wx_buffer_set.c \
	wx_f32_max.c \
	wx_f32_min.c \
	wx_frame_buffer_del.c \
	wx_frame_buffer_new.c \
	wx_socket_read.c \
	wx_socket_write.c \
	wx_packet_read_f32.c \
	wx_packet_read_u8.c \
	wx_packet_read_v2.c \
	wx_packet_write_u8.c \
	wx_time_s.c \
)
client_obj_files = $(subst $(src_dir), $(build_dir), $(client_src_files:.c=.o))
client_exe = wolf3d

editor_src_files = $(addprefix $(src_dir), \
	we_main.c \
	we_editor_new.c \
	we_editor_run.c \
	we_editor_del.c \
	we_chart_new.c \
	we_chart_del.c \
	we_init_toolbar.c \
	we_init_map.c \
	we_init_chart.c \
	we_editor_on_resize.c \
	we_position_check.c \
	we_draw.c \
	we_draw_pixel.c \
	we_draw_line.c \
	we_draw_rec.c \
	we_draw_block.c \
	we_draw_grid.c \
	we_draw_map.c \
	we_draw_toolbar.c \
	we_draw_button.c \
	wx_buffer_copy.c \
	wx_buffer_set.c \
	wx_frame_buffer_del.c \
	wx_frame_buffer_new.c \
)
editor_obj_files = $(subst $(src_dir), $(build_dir), $(editor_src_files:.c=.o))
editor_exe = wolf3d_editor

server_src_files = $(addprefix $(src_dir), \
	ws_main.c \
	ws_server_del.c \
	ws_server_network_read.c \
	ws_server_network_write.c \
	ws_server_new.c \
	ws_server_run.c \
	wx_address_equal.c \
	wx_buffer_copy.c \
	wx_buffer_set.c \
	wx_f64_min.c \
	wx_socket_read.c \
	wx_socket_write.c \
	wx_packet_read_f32.c \
	wx_packet_read_u8.c \
	wx_packet_write_f32.c \
	wx_packet_write_u8.c \
	wx_packet_write_v2.c \
	wx_time_s.c \
)
server_obj_files = $(subst $(src_dir), $(build_dir), $(server_src_files:.c=.o))
server_exe = wolf3d_server

compile_commands_files = \
	$(subst $(src_dir), $(build_dir), $(client_src_files:.c=.json)) \
	$(subst $(src_dir), $(build_dir), $(editor_src_files:.c=.json)) \
	$(subst $(src_dir), $(build_dir), $(server_src_files:.c=.json))
compile_commands_json = compile_commands.json

dependency_files = \
	$(subst $(src_dir), $(build_dir), $(client_src_files:.c=.dep)) \
	$(subst $(src_dir), $(build_dir), $(editor_src_files:.c=.dep)) \
	$(subst $(src_dir), $(build_dir), $(server_src_files:.c=.dep))
dependency_flags = -MT $(@) -MMD -MP -MF $(build_dir)$(*).dep

LD = gcc
LDFLAGS = $(libsdl2_ldflags)
CC = gcc
CFLAGS = -c -g -Wall -Werror -Wextra $(libsdl2_cflags) -I build/libsdl2/include
CPPFLAGS = -D_REENTRANT

all: $(client_exe) $(editor_exe) $(server_exe) $(compile_commands_json)

$(NAME):

$(client_exe): $(client_obj_files)
	$(LD) $(client_obj_files) $(LDFLAGS) -o $(@)

$(client_obj_files): $(libsdl2_lib)

$(editor_exe): $(editor_obj_files)
	$(LD) $(editor_obj_files) $(LDFLAGS) -o $(@)

$(editor_obj_files): $(libsdl2_lib)

$(server_exe): $(server_obj_files)
	$(LD) $(server_obj_files) $(LDFLAGS) -o $(@)

$(server_obj_files): $(libsdl2_lib)

$(build_dir):
	mkdir $(@)

$(build_dir)%.o: $(src_dir)%.c
$(build_dir)%.o: $(src_dir)%.c $(build_dir)%.dep $(build_dir)%.json | $(build_dir)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(dependency_flags) -o $(@) $(<)

$(build_dir)%.json: $(src_dir)%.c | $(build_dir)
	echo "    {" > $(@)
	echo "        \"command\": \"$(CC) $(CFLAGS) $(CPPFLAGS) -c $(<)\","  >> $(@)
	echo "        \"directory\": \"$(CURDIR)\"," >> $(@)
	echo "        \"file\": \"$(<)\"" >> $(@)
	echo "    }," >> $(@)

$(compile_commands_json): $(compile_commands_files)
	echo "[" > $(build_dir)$(@).tmp
	cat $(^) >> $(build_dir)$(@).tmp
	sed '$$d' < $(build_dir)$(@).tmp > $(build_dir)$(@)
	echo "    }" >> $(build_dir)$(@)
	echo "]" >> $(build_dir)$(@)
	cp $(build_dir)$(@) $(@)

$(dependency_files):

$(libsdl2_makefile):
	cd libsdl2 && ./configure --prefix=$(abspath $(build_dir)libsdl2) --disable-shared --disable-video-wayland
	$(MAKE) --directory=libsdl2

$(libsdl2_lib): $(libsdl2_makefile) | $(build_dir)
	$(MAKE) --directory=libsdl2 install

clean:
	if test -f $(libsdl2_makefile); then $(MAKE) AUTOMAKE=: --directory=libsdl2 clean; fi
	rm -rf $(build_dir)

fclean:
	rm -f $(compile_commands_json)
	rm -f $(client_exe)
	rm -f $(editor_exe)
	rm -f $(server_exe)
	if test -f $(libsdl2_makefile); then $(MAKE) AUTOMAKE=: --directory=libsdl2 distclean; fi
	rm -rf $(build_dir)

re: fclean all

.PHONY: all $(NAME) clean fclean re

include $(wildcard $(dependency_files))
