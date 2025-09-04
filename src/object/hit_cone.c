/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:20:18 by secros            #+#    #+#             */
/*   Updated: 2025/09/04 14:51:19 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "ray.h"

#define T_MIN 1e-4
#define EPSILON 1e-6

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

double	hit_cone_body(t_cone *co, t_ray r)
{
	const double	k = pow(co->height, 2) / (pow(co->height, 2) + pow(co->radius, 2));
	const double	m = vect3_scalar(r.direction, co->orientation);
	const t_vect3	delta_p = vect3_sub(r.origin, co->pos);
	const double	n = vect3_scalar(delta_p, co->orientation);
	const double	a = m * m - k;
	const double	b = 2 * ((n * m) - (vect3_scalar(delta_p, r.direction) * k ));
	const double	c = (n * n) - (vect3_scalar(delta_p, delta_p) * k);
	const double	delta = b * b - (4 * a * c);
	double	t[2];

	if (delta < 0)
		return (-1);
	t[0] = (-b - sqrt(delta)) / (2 * a);
	t[1] = (-b + sqrt(delta)) / (2 * a);
	if (t[0] > t[1])
		swap_doubles(&t[0], &t[1]);
	double projected_height = n + (t[0] * m);
	if (t[0] > T_MIN && projected_height >= 0 && projected_height <= co->height)
		return (t[0]);
	projected_height = n + (t[1] * m);
	if (t[1] > T_MIN && projected_height >= 0 && projected_height <= co->height)
		return (t[1]);
	return (-1);
}

double	hit_cone(t_cone *co, t_ray r)
{
	double			t_body;
	double			t_cap = 0;
	// const t_vect3	neg_ori = vect3_negate(co->orientation);
	const t_point3	bot = vect3_add(co->pos, vect3_const_mult(co->orientation, co->height));

	t_body = hit_cone_body(co, r);
	t_cap = hit_disk(r, bot, co->orientation, co->radius);
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
