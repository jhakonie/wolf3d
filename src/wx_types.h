/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 10:52:07 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/11 11:15:04 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WX_TYPES_H
# define WX_TYPES_H

/*
** 2021-03-11 todo: this could be against the norm if someone bothers to check.
** decide whether it would be alright to just use INFINITY from math.h instead
** or if there's some truly compile-time constant way of doing this
*/

# define WX_F32_INF (1.0f / 0.0f)

# define WX_NULL ((void *)0)

enum	e_bool
{
	wx_false = 0,
	wx_true = 1
};
typedef enum e_bool	t_bool;

typedef float	t_f32;

t_f32	wx_f32_max(t_f32 x0, t_f32 x1);
t_f32	wx_f32_min(t_f32 x0, t_f32 x1);

typedef double	t_f64;

t_f64	wx_f64_min(t_f64 x0, t_f64 x1);

typedef char	t_s8;
typedef int		t_s32;

typedef unsigned char	t_u8;
typedef unsigned short	t_u16;
typedef unsigned int	t_u32;
typedef unsigned long int	t_u64;

void	wx_buffer_copy(void *xs, void const *ys, t_u64 size);
void	wx_buffer_set(void *xs, t_u64 xs_size, t_u8 x);

#endif
