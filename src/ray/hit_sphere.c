/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:16:05 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/20 10:13:49 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect3.h"
#include "ray.h"

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
