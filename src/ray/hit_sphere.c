/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:16:05 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/22 10:29:41 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "miniRT.h"
#include "vect3.h"

t_vect3	cylinder_normal(t_cylinder *cy, t_vect3 p)
{
	const t_vect3	w = vect3_sub(p, cy->pos);
	const double	t = vect3_scalar(w, cy->orientation);
	const t_vect3	q = vect3_add(cy->pos, vect3_const_mult(cy->orientation, t));

	return (vect3_unit(vect3_sub(p, q)));
}

t_vect3    get_cylinder_normal(t_cylinder *cy, t_ray r, double t)
{
    const t_point3	p = ray_at(r, t);
    const t_point3	top = vect3_add(cy->pos, vect3_const_mult(cy->orientation, cy->height / 2));
    const t_point3	bot = vect3_sub(cy->pos, vect3_const_mult(cy->orientation, cy->height / 2));

    if (fabs(vect3_scalar(vect3_sub(p, bot), cy->orientation)) < EPSILON)
        return (vect3_negate(cy->orientation));
    if (fabs(vect3_scalar(vect3_sub(p, top), cy->orientation)) < EPSILON)
        return (cy->orientation);
    return (cylinder_normal(cy, p));
}

static double	hit_disk(t_ray r, t_point3 c, t_vect3 n, double rad)
{
	double	denom;
	double	t;

	denom = vect3_scalar(n, r.direction);
	if (denom > -EPSILON && denom < EPSILON)
		return (-1);
	t = vect3_scalar(n, vect3_sub(c, r.origin)) / denom;
	if (t < T_MIN)
		return (-1);
	if (vect3_norm(vect3_sub(ray_at(r, t), c).coords) > rad)
		return (-1);
	return (t);
}

double	hit_cylinder_caps(t_cylinder *cy, t_ray r)

{
	const t_point3	bot = vect3_sub(cy->pos, vect3_const_mult(cy->orientation, cy->height / 2));
	const t_point3	top = vect3_add(cy->pos, vect3_const_mult(cy->orientation, cy->height / 2));
	const double	t1 = hit_disk(r, bot, vect3_negate(cy->orientation), cy->radius);
	const double	t2 = hit_disk(r, top, cy->orientation, cy->radius);

	if (t1 > 0 && (t2 < 0 || t1 < t2))
		return (t1);
	return (t2);
}

double	hit_plane(t_plane *plane, t_ray ray)
{
	const double	sum = vect3_scalar(plane->orientation, \
		vect3_sub(plane->pos, ray.origin));
	const double	div = vect3_scalar(plane->orientation, ray.direction);
	double			t;

	if (div < EPSILON && div > -EPSILON)
		return (-1);
	t = sum / div;
	if (t < T_MIN)
		return (-1);
	return (t);
}

double	hit_sphere(t_sphere *sphere, t_ray ray)
{
	const t_vect3	oc = vect3_sub(sphere->pos, ray.origin);
	const double	h = vect3_scalar(ray.direction, oc);
	const double	c = vect3_scalar(oc, oc) - sphere->radius * sphere->radius;
	const double	discriminant = h * h - c;

	if (discriminant < 0)
		return (-1);
	return ((h - sqrt(discriminant)));
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

void	swap_d(double *v1, double *v2)
{
	const double	tmp = *v1;

	*v1 = *v2;
	*v2 = tmp;
}

double	hit_cylinder(t_cylinder *cy, t_ray r)
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
		swap_d(&hit[T1], &hit[T2]);
	return (hit_finite_cylinder(hit, scal, cy->height / 2));
}
