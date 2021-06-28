#include "wc_draw.h"
#include "wc_client.h"
#include "wx_draw.h"

static void	zz_draw_enemy(t_p3 enemy_w, t_u32 i,
				t_client *c, t_player *p)
{
	t_ray			ray;
	t_f32			angle_d;
	t_u32			old_id;
	t_u32			map_index;

	map_index = (int)(enemy_w.x / WX_TILE_WIDTH)
		+ WX_MAP_TILES_WIDTH * (int)(enemy_w.z / WX_TILE_WIDTH);
	if (map_index >= WX_MAP_SIZE || map_index < 0)
		return ;
	old_id = c->map.tiles[map_index];
	c->map.tiles[map_index] = WX_ENEMY;
	angle_d = 0;
	wx_ray_init(&ray, p->fov_d, c->frame_buffer.width, p->position);
	ray.view_height = p->height;
	while (ray.nb < c->frame_buffer.width)
	{
		ray.tile_type_to_find = WX_ENEMY;
		wx_ray_calculate(&ray, angle_d, p->direction_d);
		wx_ray_cast(&ray, c->map.tiles);
		if (ray.tile.tiles_id == WX_ENEMY)
			wc_draw_25d_enemy(&c->frame_buffer, &ray, &c->map.textures.skys[i]);
		angle_d += ray.angle_increment_d;
		ray.nb++;
	}
	c->map.tiles[map_index] = old_id;
}

static void	zz_draw_others(t_client *c, t_player *p)
{
	t_u8	i;

	i = 0;
	while (i < c->others_size)
	{
		zz_draw_enemy(c->other_positions[i], i, c, p);
		i++;
	}
}

void	wc_draw_25d(t_client *c)
{
	t_player	p;

	p.fov_d = 60;
	p.direction_d = wx_to_degrees(wx_q4_yrot(&c->player_orientation));
	p.direction_d -= 90;
	c->player_view_height += c->mouse_dy * 0.005f;
	if (c->player_view_height < 0)
		c->player_view_height = 0;
	else if (c->player_view_height > 1)
		c->player_view_height = 1;
	p.position.x = c->player_position.x - 0.5f * WX_TILE_WIDTH;
	p.position.y = c->player_position.z - 0.5f * WX_TILE_WIDTH;
	p.height = c->player_view_height;
	wx_draw_3d(&c->frame_buffer, p, &c->map);
	zz_draw_others(c, &p);
	wc_draw_copy(c, &c->frame_buffer);
}
