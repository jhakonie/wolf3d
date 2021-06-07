#include "we_path.h"
#include "stdlib.h"

static t_u64	zz_strlen(t_c8 *str)
{
	t_u32	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_bool	we_path_new(t_path *p, t_c8 *str)
{
	t_u64	len;

	len = zz_strlen(str);
	p->buffer_size = len + 1;
	p->path_size = len;
	p->buffer = (t_c8 *)malloc(sizeof(t_c8) * (p->buffer_size));
	if (!p->buffer)
		return (wx_false);
	wx_buffer_set(p->buffer, p->buffer_size, 0);
	wx_buffer_copy(p->buffer, str, len);
	p->buffer[len] = '\0';
	return (wx_true);
}
