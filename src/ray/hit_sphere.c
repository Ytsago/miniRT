/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:16:05 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/25 17:53:28 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect3.h"
#include "ray.h"

# define EPSILON 1e-6
# define T_MIN 1e-4

double	hit_plane(t_point3 pos, t_vect3 normal, t_ray ray)
{
	const double	sum = vect3_scalar(normal, vect3_sub(pos, ray.origin));
	const double	div = vect3_scalar(normal, ray.direction);
	double			t;

	if (div < EPSILON && div > -EPSILON)
		return (-1);
	t = sum / div;
	if (t < T_MIN)
		return (-1);
	return (t);
}

double	hit_sphere(t_point3 pos, double radius, t_ray ray)
{
	const t_vect3	oc = vect3_sub(pos, ray.origin);
	const double	a = vect3_scalar(ray.direction, ray.direction);
	const double	h = vect3_scalar(ray.direction, oc);
	const double	c = vect3_scalar(oc, oc) - radius * radius;
	const double	discriminant = h * h - a * c;

	if (discriminant < 0)
		return (-1);
	return ((h - sqrt(discriminant)) / a);
}
