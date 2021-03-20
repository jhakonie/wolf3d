/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:41:28 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/20 08:23:02 by ***REMOVED***         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WX_MATH_H
# define WX_MATH_H

# include "wx_types.h"

# define WX_PI (3.14159f)

/*
** 2021-03-03 todo: come up with a better names for some of these functions.
** names such as wx_m44_new_q4_p3() and wx_q4_new_v3_f32() are questionable
**
** 2021-03-04 todo: could n3, p2, p3, p4, q4 and v3 parameters be by-value?
*/

typedef struct s_m44	t_m44;
typedef struct s_p4	t_p4;
typedef struct s_q4	t_q4;
typedef struct s_v3	t_v3;

struct		s_p3
{
	t_f32	x;
	t_f32	y;
	t_f32	z;
};
typedef struct s_p3	t_p3;

struct		s_aabb
{
	t_p3	max;
	t_p3	min;
};
typedef struct s_aabb	t_aabb;

struct		s_n3
{
	t_f32	x;
	t_f32	y;
	t_f32	z;
};
typedef struct s_n3	t_n3;

struct		s_plane
{
	t_f32	d;
	t_n3	n;
};
typedef struct s_plane	t_plane;

t_plane		wx_plane_new(t_f32 a, t_f32 b, t_f32 c, t_f32 d);
t_f32		wx_plane_signed_distance_p3(t_plane const *pl, t_p3 const *p);

/*
** 2021-03-20 note: left, right, bottom, top, near, far
*/

struct		s_frustum
{
	t_plane	planes[6];
};
typedef struct s_frustum	t_frustum;

t_frustum	wx_frustum_new(t_m44 const *m);

struct		s_m44
{
	t_f32	xs[16];
};

t_m44		wx_m44_new_inverse_q4_p3(t_q4 const *q, t_p3 const *p);
t_m44		wx_m44_new_perspective(t_f32 hfov_rad, t_f32 aspect_ratio,
	t_f32 near, t_f32 far);
t_m44		wx_m44_new_q4_p3(t_q4 const *q, t_p3 const *p);
t_m44		wx_m44_mul_m44(t_m44 const *l, t_m44 const *r);
t_p3		wx_m44_mul_p3(t_m44 const *l, t_p3 const *r);
t_p4		wx_m44_mul_p4(t_m44 const *l, t_p4 const *r);

/*
** 2021-03-01 note: it's not strictly necessary or particularly error-prone not
** to define distinct c-types for normals, points and vectors. however it was
** decided to split them up hoping to make it slightly more explicit what kind
** of obejct something is in any given context
*/

struct		s_p2
{
	t_f32	x;
	t_f32	y;
};
typedef struct s_p2	t_p2;

struct		s_p4
{
	t_f32	x;
	t_f32	y;
	t_f32	z;
	t_f32	w;
};

struct		s_q4
{
	t_f32	x;
	t_f32	y;
	t_f32	z;
	t_f32	w;
};

t_q4		wx_q4_new_v3_f32(t_v3 const *axis, t_f32 rad);

struct		s_v3
{
	t_f32	x;
	t_f32	y;
	t_f32	z;
};

t_f32		wx_to_radians(t_f32 deg);

#endif
