# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/25 13:22:26 by jhakonie          #+#    #+#              #
#    Updated: 2021/01/25 18:44:59 by jhakonie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

src_dir = src/
build_dir = build/
libsdl2_makefile = libsdl2/Makefile
libsdl2_lib = $(build_dir)libsdl2/lib/libSDL2.a


editor_src_files = $(addprefix $(src_dir), \
	we_main.c\
)
editor_obj_files = $(subst $(src_dir), $(build_dir), $(editor_src_files:.c=.o))
editor_exe = wolf3d_editor

LD = gcc
LDFLAGS = -L $(build_dir)libsdl2/lib -l SDL2 
CC = gcc
CFLAGS = -c -Wall -Werror -Wextra -I $(build_dir)libsdl2/include

all: $(editor_exe)

$(editor_exe): $(build_dir) $(libsdl2_lib) $(editor_obj_files) 
	$(LD) $(editor_obj_files) $(LDFLAGS) -o $(@)

$(build_dir)%.o: $(src_dir)%.c
	# gcc -c -Wextra -Wall -Werror -o we_main.o we_main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(@) $(<)

$(build_dir):
	mkdir $(@)
	
$(libsdl2_makefile):
	cd libsdl2 && ./configure --prefix=$(abspath $(build_dir)libsdl2)
	$(MAKE) --directory=libsdl2

$(libsdl2_lib): $(libsdl2_makefile)
	$(MAKE) --directory=libsdl2 install

clean:
	if test -f $(libsdl2_lib); $(MAKE) --directory=libsdl2 clean; fi
	rm -rf $(build_dir)

fclean:
	rm -f $(editor_exe)
	if test -f $(libsdl2_lib); then $(MAKE) --directory=libsdl2 distclean; fi
	rm -rf $(build_dir)
	
re: fclean all

.PHONY: all clean fclean re