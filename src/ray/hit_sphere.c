/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:16:05 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/18 19:19:16 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect3.h"
#include "ray.h"

bool	hit_sphere(t_point3 pos, double radius, t_ray ray)

{
	const t_vect3	oc = vect3_sub(ray.origin, pos);
	const double	a = vect3_scalar(ray.direction, ray.direction);
	const double	b = -2.0 * vect3_scalar(ray.direction, oc);
	const double	c = vect3_scalar(oc, oc) - radius * radius;
	const double	discriminant = b*b - 4*a*c;
	return (discriminant >= 0);
}
