/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:16:05 by yabokhar          #+#    #+#             */
/*   Updated: 2025/07/01 17:57:20 by secros           ###   ########.fr       */
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
	const double	a = vect3_scalar(ray.direction, ray.direction);
	const double	h = vect3_scalar(ray.direction, oc);
	const double	c = vect3_scalar(oc, oc) - sphere->radius * sphere->radius;
	const double	discriminant = h * h - a * c;

	if (discriminant < 0)
		return (-1);
	return ((h - sqrt(discriminant)) / a);
}

double hit_cylinder() { return (0); }
