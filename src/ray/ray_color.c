/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:20:16 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/20 10:37:03 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vect3.h"
#include "ray.h"

t_vect3	background_shade(t_ray ray)
{
	t_vect3			unit_direction;
	const double	a = 0.5 * (unit_direction.y + 1.0);

	unit_direction = vect3_unit(ray.direction);
	return (vect3_add(vect3_const_mult(((t_vect3){1.0, 1.0, 1.0}), (1.0 - a)), \
		vect3_const_mult(((t_vect3){0.5, 0.7, 1.0}), a)));
}

t_vect3	sphere_shade(t_ray ray, t_object sphere, double t)
{
	t_vect3	normal;

	normal = vect3_unit(vect3_sub(ray_at(ray, t), sphere.pos));
	return (vect3_const_div((t_vect3){normal.x +1, normal.y +1, \
		normal.z +1}, 2));
}

t_color	ray_color(t_ray ray, t_list *objects)
{
	t_object	sphere;
	t_vect3		rgb;
	double		t;

	while (objects)
	{
		if (((t_object *)objects->content)->type == SPHERE)
		{
			sphere = *((t_object *)objects->content);
			t = hit_sphere(sphere.pos, sphere.size.x / 2, ray);
			if (t > 0.0)
			{
				rgb = sphere_shade(ray, sphere, t);
				return ((t_color){.r = 255.99 * rgb.x, \
					.g = 255.99 * rgb.y, .b = 255.99 * rgb.z, .a = 0});
			}
		}
		objects = objects->next;
	}
	rgb = background_shade(ray);
	return ((t_color){.r = rgb.x * 255.99, .g = rgb.y * 255.99, \
		.b = rgb.z * 255.99, .a = rgb.z * 255.99});
}
