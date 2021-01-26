# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/25 13:22:26 by jhakonie          #+#    #+#              #
#    Updated: 2021/01/26 22:48:10 by ***REMOVED***         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

src_dir = src/
build_dir = build/

libsdl2_makefile = libsdl2/Makefile
libsdl2_lib = $(build_dir)libsdl2/lib/libSDL2.a
libsdl2_cflags = `$(build_dir)libsdl2/bin/sdl2-config --cflags`
libsdl2_ldflags = `$(build_dir)libsdl2/bin/sdl2-config --libs`

libsdl2_net_makefile = libsdl2_net/Makefile
libsdl2_net_lib = $(build_dir)libsdl2_net/lib/libSDL2_net.a
libsdl2_net_cflags = -I $(build_dir)libsdl2/include -D_REENTRANT
libsdl2_net_ldflags = -L $(build_dir)libsdl2_net/lib -pthread -lSDL2_net -lSDL2

client_src_files = $(addprefix $(src_dir), \
	wc_main.c \
)
client_obj_files = $(subst $(src_dir), $(build_dir), $(client_src_files:.c=.o))
client_exe = wolf3d

editor_src_files = $(addprefix $(src_dir), \
	we_main.c \
)
editor_obj_files = $(subst $(src_dir), $(build_dir), $(editor_src_files:.c=.o))
editor_exe = wolf3d_editor

server_src_files = $(addprefix $(src_dir), \
	ws_main.c \
)
server_obj_files = $(subst $(src_dir), $(build_dir), $(server_src_files:.c=.o))
server_exe = wolf3d_server

compile_commands_files = \
	$(subst $(src_dir), $(build_dir), $(client_src_files:.c=.json)) \
	$(subst $(src_dir), $(build_dir), $(editor_src_files:.c=.json)) \
	$(subst $(src_dir), $(build_dir), $(server_src_files:.c=.json))
compile_commands_json = compile_commands.json

LD = gcc
LDFLAGS = $(libsdl2_ldflags) $(libsdl2_net_ldflags)
CC = gcc
CFLAGS = -c -Wall -Werror -Wextra $(libsdl2_cflags) $(libsdl2_net_cflags)
CPPFLAGS = -D_REENTRANT

all: $(client_exe) $(editor_exe) $(server_exe)

$(NAME):

$(client_exe): $(build_dir) $(libsdl2_net_lib) $(client_obj_files)
	$(LD) $(client_obj_files) $(LDFLAGS) -o $(@)

$(editor_exe): $(build_dir) $(libsdl2_lib) $(editor_obj_files)
	$(LD) $(editor_obj_files) $(LDFLAGS) -o $(@)

$(server_exe): $(build_dir) $(libsdl2_net_lib) $(server_obj_files)
	$(LD) $(server_obj_files) $(LDFLAGS) -o $(@)

$(build_dir):
	mkdir $(@)

$(build_dir)%.o: $(src_dir)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(@) $(<)

$(build_dir)%.json: $(src_dir)%.c
	echo "    {" > $(@)
	echo "        \"command\": \"$(CC) $(CFLAGS) $(CPPFLAGS) -c $(<)\","  >> $(@)
	echo "        \"directory\": \"$(CURDIR)\"," >> $(@)
	echo "        \"file\": \"$(<)\"" >> $(@)
	echo "    }," >> $(@)

$(compile_commands_json): $(build_dir) $(compile_commands_files)
	echo "[" > $(@).tmp
	cat $(compile_commands_files) >> $(@).tmp
	sed '$$d' < $(@).tmp > $(@)
	echo "    }" >> $(@)
	echo "]" >> $(@)
	rm $(@).tmp

$(libsdl2_makefile):
	cd libsdl2 && ./configure --prefix=$(abspath $(build_dir)libsdl2) --disable-shared --disable-video-wayland
	$(MAKE) --directory=libsdl2

$(libsdl2_lib): $(libsdl2_makefile)
	$(MAKE) --directory=libsdl2 install

# 2021-01-26 todo: horrible hack, AUTOMAKE=:, to fix build on linux
# errors out with weird complaint about: "automake-1.13 not found"
$(libsdl2_net_makefile): $(libsdl2_lib)
	cd libsdl2_net && ./configure --prefix=$(abspath $(build_dir)libsdl2_net) --with-sdl-prefix=$(abspath $(build_dir)libsdl2) --disable-shared
	$(MAKE) AUTOMAKE=: --directory=libsdl2_net

$(libsdl2_net_lib): $(libsdl2_net_makefile)
	$(MAKE) AUTOMAKE=: --directory=libsdl2_net install

clean:
	if test -f $(libsdl2_makefile); then $(MAKE) --directory=libsdl2 clean; fi
	if test -f $(libsdl2_net_makefile); then $(MAKE) --directory=libsdl2_net clean; fi
	rm -rf $(build_dir)

fclean:
	rm -f $(client_exe)
	rm -f $(editor_exe)
	rm -f $(server_exe)
	if test -f $(libsdl2_makefile); then $(MAKE) --directory=libsdl2 distclean; fi
	if test -f $(libsdl2_net_makefile); then $(MAKE) --directory=libsdl2_net clean; fi
	rm -rf $(build_dir)

re: fclean all

.PHONY: all $(NAME) clean fclean re
