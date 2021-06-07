#include "we_path.h"
#include "stdlib.h"

static t_u64	zz_strlen(t_c8 *str)
{
	t_u64	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	zz_copy(t_path *p, t_c8 *str, t_u64 len, t_u64 new_path_size)
{
	wx_buffer_copy(p->buffer + p->path_size, str, len);
	p->buffer[new_path_size] = '\0';
}

t_bool	we_path_add_back(t_path *p, t_c8 *str)
{
	t_u64	new_buffer_size;
	t_u64	new_path_size;
	t_c8	*new_buffer;
	t_u64	len;

	len = zz_strlen(str);
	new_path_size = len + p->path_size;
	if (new_path_size >= p->buffer_size)
	{
		new_buffer_size = 2 * new_path_size;
		new_buffer = (t_c8 *)malloc(sizeof(t_c8) * (new_buffer_size));
		if (!new_buffer)
			return (wx_false);
		wx_buffer_set(new_buffer, new_buffer_size, 0);
		wx_buffer_copy(new_buffer, p->buffer, p->path_size);
		wx_buffer_copy(new_buffer + p->path_size, str, len);
		new_buffer[new_path_size] = '\0';
		free(p->buffer);
		p->buffer = new_buffer;
		p->buffer_size = new_buffer_size;
	}
	else
		zz_copy(p, str, len, new_path_size);
	p->path_size = new_path_size;
	return (wx_true);
}
