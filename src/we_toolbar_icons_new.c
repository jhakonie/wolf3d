#include "we_editor.h"

t_bool	we_toolbar_icons_new(t_tool *t)
{
	wx_buffer_set(t, sizeof(t[0].button.icon.buffer), 0);
	if (!we_texture_new("data/editor/wall.xpm", &t[1].button.icon))
		return (we_toolbar_icons_del(t));
	if (!we_texture_new("data/editor/door.xpm", &t[2].button.icon))
		return (we_toolbar_icons_del(t));
	if (!we_texture_new("data/editor/player.xpm", &t[3].button.icon))
		return (we_toolbar_icons_del(t));
	if (!we_texture_new("data/editor/floor.xpm", &t[4].button.icon))
		return (we_toolbar_icons_del(t));
	if (!we_texture_new("data/editor/save.xpm", &t[5].button.icon))
		return (we_toolbar_icons_del(t));
	return (wx_true);
}
