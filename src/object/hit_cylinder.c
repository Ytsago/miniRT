/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:16:05 by yabokhar          #+#    #+#             */
/*   Updated: 2025/09/02 11:25:08 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "miniRT.h"
#include "vect3.h"

#define N 0
#define M 1
#define T1 0
#define T2 1
#define A 0
#define B 1
#define C 2
#define EPSILON 1e-4
#define T_MIN 1e-6

static double	hit_disk(t_ray r, t_point3 cap_pos, t_vect3 n, double rad)

{
	double	denom;
	double	t;

	denom = vect3_scalar(n, r.direction);
	if (denom > -EPSILON && denom < EPSILON)
		return (-1);
	t = vect3_scalar(n, vect3_sub(cap_pos, r.origin)) / denom;
	if (t < T_MIN)
		return (-1);
	if (vect3_norm(vect3_sub(ray_at(r, t), cap_pos).coords) > rad)
		return (-1);
	return (t);
}

double	hit_cylinder_caps(t_cylinder *cy, t_ray r)

{
	const double	t1 = hit_disk(r, cy->bot, \
	vect3_negate(cy->orientation), cy->radius);
	const double	t2 = hit_disk(r, cy->top, \
	cy->orientation, cy->radius);

	if (t1 > 0 && (t2 < 0 || t1 < t2))
		return (t1);
	return (t2);
}

double	hit_finite_cylinder(double hit[2], double scal[2], double height)
{
	double	y1;
	double	y2;

	y1 = scal[N] + hit[T1] * scal[M];
	if (hit[T1] > T_MIN && y1 >= -height && y1 <= height)
		return (hit[T1]);
	y2 = scal[N] + hit[T2] * scal[M];
	if (hit[T2] > T_MIN && y2 >= -height && y2 <= height)
		return (hit[T2]);
	return (-1);
}

double	hit_cylinder_body(t_cylinder *cy, t_ray r)
{
	const t_vect3	w = vect3_sub(r.origin, cy->pos);
	double			scal[2];
	double			fact[3];
	double			hit[2];
	double			delta;

	scal[N] = vect3_scalar(w, cy->orientation);
	scal[M] = vect3_scalar(r.direction, cy->orientation);
	fact[A] = 1 - (scal[M] * scal[M]);
	fact[B] = vect3_scalar(w, r.direction) - scal[N] * scal[M];
	fact[C] = vect3_scalar(w, w) - scal[N] * scal[N] - cy->radius * cy->radius;
	delta = fact[B] * fact[B] - fact[A] * fact[C];
	if (delta < 0)
		return (-1);
	hit[T1] = (-fact[B] - sqrt(delta)) / fact[A];
	hit[T2] = (-fact[B] + sqrt(delta)) / fact[A];
	if (hit[T1] > hit[T2])
		swap_doubles(&hit[T1], &hit[T2]);
	return (hit_finite_cylinder(hit, scal, cy->height / 2));
}

double	hit_cylinder(t_cylinder *cy, t_ray r)
{
	double	t_body;
	double	t_caps;

	t_body = hit_cylinder_body(cy, r);
	t_caps = hit_cylinder_caps(cy, r);

	if (t_body > 0 && t_caps > 0)
	{
		if (t_body < t_caps)
			return (t_body);
		return (t_caps);
	}
	if (t_body > 0)
		return (t_body);
	return (t_caps);
}
