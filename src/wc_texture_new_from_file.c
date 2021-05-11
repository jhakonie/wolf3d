#include "stdlib.h"

#include "wc_draw.h"
#include "wx_parse_xpm.h"

/*
** 2021-05-01 todo: stealing the buffer and the buffer_size calculation are
** brittle. the buffer_size relies on what wx_parse_xpm_pixels() does
** internally. rather include the size in the xpm struct.
*/
t_bool	wc_texture_new_from_file(t_texture *t, char const *filename)
{
	t_xpm	xpm;

	if (!wx_parse_xpm(filename, &xpm))
	{
		return (wx_false);
	}
	t->buffer = (t_u8 *)xpm.pixels;
	t->buffer_size = xpm.width * xpm.height * sizeof(*xpm.pixels);
	t->width = xpm.width;
	t->height = xpm.height;
	xpm.pixels = WX_NULL;
	wx_xpm_del(&xpm);
	return (wx_true);
}
