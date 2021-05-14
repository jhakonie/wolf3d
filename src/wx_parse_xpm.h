/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_parse_xpm.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:21:55 by jhakonie          #+#    #+#             */
/*   Updated: 2021/05/14 16:04:31 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WX_PARSE_XPM_H
# define WX_PARSE_XPM_H

# include "wx_types.h"
# include "wx_parse.h"
# include "unistd.h"
# include "stdlib.h"

# define WX_XPM_FREE_TABLE (1)
# define WX_XPM_FREE_PIXELS (2)
# define FNV_OFFSET (14695981039346656037UL)
# define FNV_PRIME (1099511628211UL)

typedef struct s_key_value
{
	t_u32		value;
	const t_c8	*key;

}	t_key_value;

typedef struct s_parse_xpm_index
{
	t_u32	w;
	t_u32	h;
	t_u32	key_index;
	t_u32	pixel_index;
}	t_parse_xpm_index;

typedef struct s_xpm
{
	t_u32		width;
	t_u32		height;
	t_u32		color_count;
	t_u32		keyword_length;
	t_u32		size;
	t_u32		*pixels;
	t_key_value	*table;
	t_u32		table_size;
}	t_xpm;

t_bool	wx_parse_xpm(t_c8 const *filename, t_xpm *xpm);
t_bool	wx_parse_hex(t_u8 *str, t_u32 *hex, t_u32 len);
t_bool	wx_parse_until(t_parse_context *pc, t_u8 const c);
t_bool	wx_parse_xpm_comment(t_parse_context *pc);
t_bool	wx_parse_xpm_error(t_xpm *xpm, t_u32 error,
			t_c8 *error_message, t_u32 len);
t_bool	wx_parse_xpm_colors(t_parse_context *pc, t_xpm *xpm);
t_bool	wx_parse_xpm_pixels(t_parse_context *pc, t_xpm *xpm);
void	wx_xpm_del(t_xpm *xpm);
t_u64	wx_parse_xpm_hash_key(const t_c8 *key, t_u32 size);

#endif
