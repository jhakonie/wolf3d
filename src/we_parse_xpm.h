/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_parse_xpm.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:21:55 by jhakonie          #+#    #+#             */
/*   Updated: 2021/04/12 22:56:40 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WE_PARSE_XPM_H
# define WE_PARSE_XPM_H

# include "wx_types.h"
# include "wx_parse.h"
# include "unistd.h"
# include "stdlib.h"

# define WE_XPM_FREE_KEY (1)
# define WE_XPM_FREE_KEYWORD (2)
# define WE_XPM_FREE_PIXELS (3)

typedef struct s_color_key
{
	t_u32	color;
	t_u8	*keyword;

}					t_color_key;

typedef struct s_parse_xpm_index
{
	t_u32		w;
	t_u32		h;
	t_u32		key_index;
	t_u32		pixel_index;
}					t_parse_xpm_index;

typedef struct s_xpm
{
	t_u32				width;
	t_u32				height;
	t_u32				color_count;
	t_u32				keyword_length;
	t_color_key			*key;
	t_u32				*pixels;

}					t_xpm;

t_bool	we_parse_xpm(char *filename, t_xpm *xpm);
t_bool	we_parse_hexa(t_u8 *str, t_u32 *hex, t_u32 len);
t_bool	we_parse_until(t_parse_context *pc, t_u8 const c);
t_bool	we_parse_xpm_comment(t_parse_context *pc);
t_bool	we_parse_xpm_error(t_xpm *xpm, t_u32 error, t_u32 index);
t_bool	we_parse_xpm_colors(t_xpm *xpm, t_parse_context *pc);
t_bool	we_parse_xpm_pixels(t_xpm *xpm, t_parse_context *pc);
void	we_xpm_del(t_xpm *xpm);

#endif
