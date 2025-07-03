/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:16:05 by yabokhar          #+#    #+#             */
/*   Updated: 2025/07/03 11:28:00 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "vect3.h"

#define EPSILON	1e-6
#define T_MIN	1e-4

double	hit_plane(t_plane *plane, t_ray ray) {
	const double	sum = vect3_scalar(plane->orientation, vect3_sub(plane->pos, ray.origin));
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
	//const double	a = vect3_scalar(ray.direction, ray.direction);
	const double	h = vect3_scalar(ray.direction, oc);
	const double	c = vect3_scalar(oc, oc) - sphere->radius * sphere->radius;
	const double	discriminant = h * h - c;

	if (discriminant < 0)
		return (-1);
	return ((h - sqrt(discriminant)));
}

double	hit_cylinder(t_cylinder *cyl, t_ray r)
{
	const t_vect3	w = vect3_sub(r.origin, cyl->pos);
	const double	n = vect3_scalar(w, cyl->orientation);
	const double	m = vect3_scalar(r.direction, cyl->orientation);
	const double	a = 1 - (m * m);
	const double	h = vect3_scalar(w, r.direction) - n * m;
	const double	c = vect3_scalar(w, w) - n * n - cyl->radius * cyl->radius;
	const double	delta = h * h - a * c;

	if (delta < 0)
		return (-1);
	return ((-h - sqrt(delta)) / a);
}
