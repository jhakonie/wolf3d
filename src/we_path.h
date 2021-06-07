#ifndef WE_PATH_H
# define WE_PATH_H

# include "wx_types.h"
# include "wx_math.h"
# include "wx_frame_buffer.h"

struct		s_path
{	
	t_c8	*buffer;
	t_u64	buffer_size;
	t_u64	path_size;
};
typedef struct s_path	t_path;

enum e_file
{	
	we_map = 0,
	we_wall_north = 1,
	we_wall_east = 2,
	we_wall_south = 3,
	we_wall_west = 4,
	we_floor = 5,
	we_sky = 6,
	we_door = 7
}	t_file;

t_bool	we_path_new(t_path *p, t_c8 *str);
t_bool	we_path_add_back(t_path *p, t_c8 *str);
void	we_path_del(t_path *p);

#endif
