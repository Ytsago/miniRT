/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:20:16 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/18 19:20:49 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vect3.h"
#include "ray.h"

t_color ray_color(t_ray dir, t_list *objects)

{
	t_object	sphere;

	while (objects)
	{
		if (((t_object *)objects->content)->type == SPHERE)
		{
			sphere = *((t_object *)objects->content);
			if (hit_sphere(sphere.pos, sphere.size.x / 2, dir))
				return (sphere.color);
		}
		objects = objects->next;
	}

    t_vect3	unit_direction = vect3_unit(dir.direction);
    double	a = 0.5*(unit_direction.y + 1.0);
	t_vect3	rgb = vect3_add(vect3_const_mult(((t_vect3) {1.0, 1.0, 1.0}), (1.0-a)), vect3_const_mult(((t_vect3) {0.5, 0.7, 1.0}), a));
	return ((t_color) {.r = rgb.x * 255.99 , .g = rgb.y * 255.99, .b = rgb.z * 255.99, .a = rgb.z * 255.99});
}
