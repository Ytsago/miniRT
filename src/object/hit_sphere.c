/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:51:12 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/23 19:51:26 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "miniRT.h"
#include "vect3.h"

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
