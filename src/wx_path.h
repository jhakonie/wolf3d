#ifndef WX_PATH_H
# define WX_PATH_H

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
	we_door = 6,
	we_sky_north = 7,
	we_sky_east = 8,
	we_sky_south = 9,
	we_sky_west = 10
};
typedef enum e_file		t_file;

t_bool	wx_path_new(t_path *p, t_c8 const *str);
t_bool	wx_path_new3(t_path	*p, t_c8 const *start, t_c8 const *middle,
			t_c8 const *end);
t_bool	wx_path_add_back(t_path *p, t_c8 const *str);
void	wx_path_del(t_path *p);

#endif
