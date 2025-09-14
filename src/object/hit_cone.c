/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:20:18 by secros            #+#    #+#             */
/*   Updated: 2025/09/11 19:20:42 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "ray.h"

#define T_MIN 1e-4
#define EPSILON 1e-6
#define N 0
#define M 1
#define T1 0
#define T2 1
#define A 0
#define B 1
#define C 2

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

double	hit_finit_cone(double hit[2], double scal[2], double height)
{
	double projected_height;

	projected_height = scal[N] + (hit[T1] * scal[M]);
	if (hit[T1] > T_MIN && projected_height >= -height && projected_height <= height)
		return (hit[T1]);
	projected_height = scal[N] + (hit[T2] * scal[M]);
	if (hit[T2] > T_MIN && projected_height >= -height && projected_height <= height)
		return (hit[T2]);
	return (-1);
}

double	hit_cone_body(t_cone *co, t_ray r)
{
	double			scal[2];
	double			fact[3];
	double			delta;
	double			hit[2];
	const t_vect3	delta_p = vect3_sub(r.origin, co->pos);

	scal[M] = vect3_scalar(r.direction, co->orientation);
	scal[N] = vect3_scalar(delta_p, co->orientation);
	fact[A] = scal[M] * scal[M] - co->k;
	fact[B] = 2 * ((scal[N] * scal[M]) - \
		(vect3_scalar(delta_p, r.direction) * co->k));
	fact[C] = (scal[N] * scal[N]) - (vect3_scalar(delta_p, delta_p) * co->k);
	delta = fact[B] * fact[B] - (4 * fact[A] * fact[C]);
	if (delta < 0)
		return (-1);
	hit[T1] = (-fact[B] - sqrt(delta)) / (2 * fact[A]);
	hit[T2] = (-fact[B] + sqrt(delta)) / (2 * fact[A]);
	if (hit[T1] > hit[T2])
		swap_doubles(&hit[T1], &hit[T2]);
	return (hit_finit_cone(hit, scal, co->height));
}

double	hit_cone(t_cone *co, t_ray r)
{
	double			t_body;
	double			t_cap = 0;

	t_body = hit_cone_body(co, r);
	t_cap = hit_disk(r, co->bot, co->orientation, co->radius);
	if (t_body > 0 && t_cap > 0)
	{
		if (t_body < t_cap)
			return (t_body);
		return (t_cap);
	}
	if (t_body > 0)
		return (t_body);
	return (t_cap);
}
