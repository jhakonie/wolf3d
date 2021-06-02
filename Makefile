# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/25 13:22:26 by jhakonie          #+#    #+#              #
#    Updated: 2021/06/02 12:00:40 by jhakonie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

src_dir = src/
include_dirs = src/ build/libsdl2/include/
build_dir = build/

libsdl2_makefile = libsdl2/Makefile
libsdl2_lib = $(build_dir)libsdl2/lib/libSDL2.a
libsdl2_cflags = `$(build_dir)libsdl2/bin/sdl2-config --cflags`
libsdl2_ldflags = `$(build_dir)libsdl2/bin/sdl2-config --libs`

client_src_files = $(addprefix $(src_dir), \
	wc_client_dispatch_events.c \
	wc_client_del.c \
	wc_client_new.c \
	wc_client_on_resize.c \
	wc_client_run.c \
	wc_draw.c \
	wc_draw_add_visible.c \
	wc_draw_clear.c \
	wc_draw_clip.c \
	wc_draw_copy.c \
	wc_draw_face.c \
	wc_draw_face_context_new.c \
	wc_draw_face_context_reset.c \
	wc_draw_mesh.c \
	wc_draw_rectangle_solid.c \
	wc_draw_rectangle_outline.c \
	wc_depth_buffer_del.c \
	wc_depth_buffer_get.c \
	wc_depth_buffer_new.c \
	wc_depth_buffer_set.c \
	wc_main.c \
	wc_map_mesh_del.c \
	wc_map_mesh_new_from_map.c \
	wc_map_mesh_new_from_map_east.c \
	wc_map_mesh_new_from_map_floor.c \
	wc_map_mesh_new_from_map_north.c \
	wc_map_mesh_new_from_map_south.c \
	wc_map_mesh_new_from_map_west.c \
	wc_map_new_from_file.c \
	wc_mesh_aabb.c \
	wc_mesh_del.c \
	wc_mesh_new_from_file.c \
	wc_n3s_add_back.c \
	wc_n3s_del.c \
	wc_n3s_new.c \
	wc_obj_vertices_add_back.c \
	wc_obj_vertices_del.c \
	wc_obj_vertices_new.c \
	wc_p2_lerp.c \
	wc_p2s_add_back.c \
	wc_p2s_del.c \
	wc_p2s_new.c \
	wc_p3_lerp.c \
	wc_p3s_add_back.c \
	wc_p3s_del.c \
	wc_p3s_new.c \
	wc_parse_obj.c \
	wc_parse_obj_comment.c \
	wc_parse_obj_context_del.c \
	wc_parse_obj_context_new.c \
	wc_parse_obj_face.c \
	wc_parse_obj_material_filename.c \
	wc_parse_obj_material_name.c \
	wc_parse_obj_normal.c \
	wc_parse_obj_object_name.c \
	wc_parse_obj_position.c \
	wc_parse_obj_smoothing.c \
	wc_parse_obj_uv.c \
	wc_parse_u16.c \
	wc_pipeline_buffers_del.c \
	wc_pipeline_buffers_new.c \
	wc_remote_server_new.c \
	wc_remote_server_del.c \
	wc_remote_server_read.c \
	wc_remote_server_write.c \
	wc_screen_xy_aabb.c \
	wc_screen_xy_area.c \
	wc_texture_del.c \
	wc_texture_get.c \
	wc_texture_new_from_file.c \
	wc_u16s_add_back.c \
	wc_u16s_del.c \
	wc_u16s_new.c \
	wc_vertices_add_back.c \
	wc_vertices_del.c \
	wc_vertices_new.c \
	wx_address_equal.c \
	wx_buffer_copy.c \
	wx_buffer_set.c \
	wx_c8s_del.c \
	wx_c8s_new_from_file.c \
	wx_f32_lerp.c \
	wx_f32_max.c \
	wx_f32_min.c \
	wx_f64_min.c \
	wx_frame_buffer_del.c \
	wx_frame_buffer_new.c \
	wx_frame_buffer_set.c \
	wx_frustum_aabb_test.c \
	wx_frustum_new.c \
	wx_m44_mul_m44.c \
	wx_m44_mul_p3.c \
	wx_m44_mul_p3_f32.c \
	wx_m44_mul_p4.c \
	wx_m44_new_inverse_q4_p3.c \
	wx_m44_new_perspective.c \
	wx_m44_new_q4_p3.c \
	wx_obb_new.c \
	wx_packet_read_f32.c \
	wx_packet_read_u8.c \
	wx_packet_read_p3.c \
	wx_packet_read_q4.c \
	wx_packet_write_f32.c \
	wx_packet_write_q4.c \
	wx_packet_write_u8.c \
	wx_parse_f32.c \
	wx_parse_hex.c \
	wx_parse_keyword.c \
	wx_parse_until.c \
	wx_parse_whitespace.c \
	wx_parse_xpm.c \
	wx_parse_xpm_colors.c \
	wx_parse_xpm_comment.c \
	wx_parse_xpm_error.c \
	wx_parse_xpm_pixels.c \
	wx_parse_xpm_hash_key.c \
	wx_plane_new.c \
	wx_plane_line_test.c \
	wx_plane_signed_distance_n3.c \
	wx_plane_signed_distance_p3.c \
	wx_q4_mul_q4.c \
	wx_q4_new_v3_f32.c \
	wx_q4_normalize.c \
	wx_socket_read.c \
	wx_socket_write.c \
	wx_to_radians.c \
	wx_time_s.c \
	wx_xpm_del.c \
)
client_obj_files = $(subst $(src_dir), $(build_dir), $(client_src_files:.c=.o))
client_exe = wolf3d

editor_src_files = $(addprefix $(src_dir), \
	we_main.c \
	we_editor_new.c \
	we_editor_run.c \
	we_editor_del.c \
	we_window_event.c \
	we_wall_type_new.c \
	we_wall_type_del.c \
	we_texture_new.c \
	we_init_toolbar.c \
	we_init_map.c \
	we_init_tiles.c \
	we_tiles_set.c \
	we_init_player.c \
	we_init_buttons.c \
	we_from_win_to_map.c \
	we_from_map_to_win.c \
	we_save_win_to_map.c \
	we_save_map_to_file.c \
	we_mouse_event.c \
	we_mouse_pos_tool.c \
	we_mouse_pos_grid.c \
	we_key_event.c \
	we_player_move.c \
	we_player_rotate.c \
	we_to_rad.c \
	we_ray_cast.c \
	we_ray_init.c \
	we_ray_calculate.c \
	we_wall_compass_direction.c \
	we_init_triangle.c \
	we_init_line.c \
	we_draw.c \
	we_draw_to_window.c \
	we_draw_3d.c \
	we_draw_pixel.c \
	we_draw_line.c \
	we_draw_rectangle.c \
	we_draw_triangle.c \
	we_draw_grid.c \
	we_draw_map.c \
	we_draw_toolbar.c \
	we_draw_button.c \
	we_draw_player.c \
	we_draw_rays.c \
	we_draw_floor.c \
	we_floor_draw_end.c \
	we_draw_wall.c \
	we_draw_texture_wall.c \
	we_shade_pixel.c \
	we_fractal_texture_create.c \
	we_fractal.c \
	we_complex_num_arithmetic.c \
	wx_buffer_copy.c \
	wx_buffer_set.c \
	wx_c8s_new_from_file.c \
	wx_c8s_del.c \
	wx_frame_buffer_del.c \
	wx_frame_buffer_new.c \
	wx_parse_keyword.c \
	wx_parse_f32.c \
	wx_parse_hex.c \
	wx_parse_until.c \
	wx_parse_whitespace.c \
	wx_parse_xpm.c \
	wx_parse_xpm_colors.c \
	wx_parse_xpm_error.c \
	wx_parse_xpm_pixels.c \
	wx_parse_xpm_comment.c \
	wx_parse_xpm_hash_key.c \
	wx_to_radians.c \
	wx_u64_max.c \
	wx_xpm_del.c \
	wx_time_s.c \
	wx_f64_min.c \
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
	wx_p3_add_v3.c \
	wx_packet_read_f32.c \
	wx_packet_read_q4.c \
	wx_packet_read_u8.c \
	wx_packet_write_f32.c \
	wx_packet_write_u8.c \
	wx_packet_write_p3.c \
	wx_packet_write_q4.c \
	wx_q4_mul_q4.c \
	wx_q4_new_v3_f32.c \
	wx_q4_rot_v3.c \
	wx_time_s.c \
	wx_to_radians.c \
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
LDFLAGS = $(libsdl2_ldflags) #-fsanitize=address
CC = gcc
CFLAGS = -g -c -Wall -Werror -Wextra $(addprefix -I, $(include_dirs)) $(libsdl2_cflags) #-fsanitize=address
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
