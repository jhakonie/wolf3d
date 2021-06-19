#include "wc_draw.h"
#include "wx_parse.h"

struct	s_parse_map_context
{
	t_u32	x;
	t_u32	y;
};
typedef struct s_parse_map_context	t_parse_map_context;

static t_bool	zz_parse_map_tile(t_parse_context *pc, t_parse_map_context *pmc,
	t_map *m)
{
	if (pc->p >= pc->e)
	{
		return (wx_false);
	}
	if (*pc->p != '.'
		&& *pc->p != '1'
		&& *pc->p != '2'
		&& *pc->p != '3')
	{
		return (wx_false);
	}
	if (*pc->p == '.')
		m->tiles[pmc->y * m->width + pmc->x] = 0;
	else
		m->tiles[pmc->y * m->width + pmc->x] = *pc->p - '0';
	++pc->p;
	++pmc->x;
	return (wx_true);
}

static t_bool	zz_parse_map_row(t_parse_context *pc, t_parse_map_context *pmc,
	t_map *m)
{
	t_c8 const	*b;
	t_u32		x;

	b = pc->p;
	x = pmc->x;
	pmc->x = 0;
	while (pmc->x < m->width && zz_parse_map_tile(pc, pmc, m))
	{
		wx_parse_keyword(pc, " ");
	}
	if (pmc->x != m->width)
	{
		pmc->x = x;
		pc->p = b;
		return (wx_false);
	}
	++pmc->y;
	return (wx_true);
}

static t_bool	zz_parse_map(t_parse_context *pc, t_map *m)
{
	t_parse_map_context	pmc;

	pmc = (t_parse_map_context){0, 0};
	while (pmc.y < m->height && zz_parse_map_row(pc, &pmc, m))
	{
		wx_parse_keyword(pc, "\n");
	}
	if (pmc.x != m->width || pmc.y != m->height)
	{
		return (wx_false);
	}
	return (wx_true);
}

t_bool	wc_map_new_from_file(t_map *m, char const *filename)
{
	t_c8s				fb;
	t_parse_context		pc;

	if (!wx_c8s_new_from_file(&fb, 8192, filename))
	{
		return (wx_false);
	}
	pc.p = (t_c8 const *)fb.buffer;
	pc.e = (t_c8 const *)(fb.buffer + fb.size);
	m->width = WC_MAP_WIDTH;
	m->height = WC_MAP_WIDTH;
	if (!zz_parse_map(&pc, m))
	{
		wx_c8s_del(&fb);
		return (wx_false);
	}
	m->tile_width = WX_TILE_WIDTH;
	m->wall_height = WX_TILE_WIDTH;
	wx_c8s_del(&fb);
	return (wx_true);
}
