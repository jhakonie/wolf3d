/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wx_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:41:28 by ***REMOVED***          #+#    #+#             */
/*   Updated: 2021/03/30 06:50:35 by ***REMOVED***         ###   ########.fr       */
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

typedef struct s_m44		t_m44;
typedef struct s_p4			t_p4;
typedef struct s_q4			t_q4;
typedef struct s_v3			t_v3;

struct		s_p3
{
	t_f32	x;
	t_f32	y;
	t_f32	z;
};
typedef struct s_p3			t_p3;

t_p3			wx_p3_add_v3(t_p3 const *l, t_v3 const *r);

struct		s_aabb
{
	t_p3	max;
	t_p3	min;
};
typedef struct s_aabb		t_aabb;

struct		s_n3
{
	t_f32	x;
	t_f32	y;
	t_f32	z;
};
typedef struct s_n3			t_n3;

enum	e_plane_line
{
	wx_plane_line_out,
	wx_plane_line_going_in,
	wx_plane_line_going_out,
	wx_plane_line_in
};
typedef enum e_plane_line	t_plane_line;

struct		s_plane
{
	t_f32	d;
	t_n3	n;
};
typedef struct s_plane		t_plane;

t_plane			wx_plane_new(t_f32 a, t_f32 b, t_f32 c, t_f32 d);
t_plane_line	wx_plane_line_test(t_plane const *pl, t_p3 const *p0,
					t_p3 const *p1, t_f32 *t);
t_f32			wx_plane_signed_distance_n3(t_plane const *p, t_n3	const *n);
t_f32			wx_plane_signed_distance_p3(t_plane const *pl, t_p3 const *p);

/*
** 2021-03-18 todo: unify the naming of enumeration values across different
** enums. should they be: "xx_full_name_value", "xx_fn_value" or "fn_value" for
** example?
*/

enum	e_frustum_aabb
{
	wx_frustum_aabb_all_out = 0,
	wx_frustum_aabb_left = 1 << 0,
	wx_frustum_aabb_right = 1 << 1,
	wx_frustum_aabb_bottom = 1 << 2,
	wx_frustum_aabb_top = 1 << 3,
	wx_frustum_aabb_near = 1 << 4,
	wx_frustum_aabb_far = 1 << 5,
	wx_frustum_aabb_all_in = 1 << 6
};
typedef enum e_frustum_aabb	t_frustum_aabb;

enum	e_plane_obb
{
	wx_plane_obb_out = 0,
	wx_plane_obb_intersect = 1 << 0,
	wx_plane_obb_in = 1 << 1
};
typedef enum e_plane_obb	t_plane_obb;

/*
** 2021-03-20 note: left, right, bottom, top, near, far
*/

struct		s_frustum
{
	t_plane	planes[6];
};
typedef struct s_frustum	t_frustum;

t_frustum		wx_frustum_new(t_m44 const *m);
t_frustum_aabb	wx_frustum_aabb_test(t_frustum const *f, t_aabb const *aabb,
					t_m44 const *b_from_a);

struct		s_m44
{
	t_f32	xs[16];
};

t_m44			wx_m44_new_inverse_q4_p3(t_q4 const *q, t_p3 const *p);
t_m44			wx_m44_new_perspective(t_f32 hfov_rad, t_f32 aspect_ratio,
					t_f32 near, t_f32 far);
t_m44			wx_m44_new_q4_p3(t_q4 const *q, t_p3 const *p);
t_m44			wx_m44_mul_m44(t_m44 const *l, t_m44 const *r);
t_p3			wx_m44_mul_p3(t_m44 const *l, t_p3 const *r);
t_p4			wx_m44_mul_p3_f32(t_m44 const *l, t_p3 const *r, t_f32 w);
t_p4			wx_m44_mul_p4(t_m44 const *l, t_p4 const *r);

struct		s_obb
{
	t_p3	center;
	t_f32	extents2[3];
	t_n3	axes[3];
};
typedef struct s_obb		t_obb;

t_obb			wx_obb_new(t_aabb const *aabb, t_m44 const *b_from_a);

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
typedef struct s_p2			t_p2;

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

t_q4			wx_q4_new_v3_f32(t_v3 const *axis, t_f32 rad);
t_q4			wx_q4_mul_q4(t_q4 const *l, t_q4 const *r);
void			wx_q4_normalize(t_q4 *q);
t_v3			wx_q4_rot_v3(t_q4 const *q, t_v3 const *v);

struct		s_v3
{
	t_f32	x;
	t_f32	y;
	t_f32	z;
};

t_f32			wx_to_radians(t_f32 deg);

#endif
