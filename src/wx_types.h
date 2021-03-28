/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 10:52:07 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/24 14:26:15 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WX_TYPES_H
# define WX_TYPES_H

# include "math.h"

/*
** 2021-03-24 todo: since (1.0f / 0.0f) was against the norm 3 for now alias
** INFINITY from math.h for now. remove this in the future
*/
# define WX_F32_INF INFINITY

# define WX_NULL ((void *)0)

enum	e_bool
{
	wx_false = 0,
	wx_true = 1
};
typedef enum e_bool			t_bool;

typedef char				t_c8;

typedef float				t_f32;

t_f32	wx_f32_max(t_f32 x0, t_f32 x1);
t_f32	wx_f32_min(t_f32 x0, t_f32 x1);

typedef double				t_f64;

t_f64	wx_f64_min(t_f64 x0, t_f64 x1);

typedef signed char			t_s8;
typedef int					t_s32;

typedef unsigned char		t_u8;
typedef unsigned short		t_u16;
typedef unsigned int		t_u32;
typedef unsigned long int	t_u64;

void	wx_buffer_copy(void *xs, void const *ys, t_u64 size);
void	wx_buffer_set(void *xs, t_u64 xs_size, t_u8 x);

#endif
