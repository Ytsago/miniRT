/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:20:16 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/19 17:00:25 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vect3.h"
#include "ray.h"

t_color ray_color(t_ray dir, t_list *objects)

{
	t_object	sphere;
	t_vect3		color;
	double		t;

	while (objects)
	{
		if (((t_object *)objects->content)->type == SPHERE)
		{
			sphere = *((t_object *)objects->content);
			t = hit_sphere(sphere.pos, sphere.size.x / 2, dir);
			if (t > 0.0)
			{
				t_vect3	N = vect3_unit(vect3_sub(ray_at(dir, t), sphere.pos));
				color = vect3_const_div((t_vect3){N.x +1, N.y +1, N.z +1}, 2);
				return ((t_color) {.r = 255.99 * color.x, .g = 255.99 * color.y, .b = 255.99 * color.z, .a = 0});
			}
		}
		objects = objects->next;
	}
    t_vect3	unit_direction = vect3_unit(dir.direction);
    double	a = 0.5*(unit_direction.y + 1.0);
	t_vect3	rgb = vect3_add(vect3_const_mult(((t_vect3) {1.0, 1.0, 1.0}), (1.0-a)), vect3_const_mult(((t_vect3) {0.5, 0.7, 1.0}), a));
	return ((t_color) {.r = rgb.x * 255.99 , .g = rgb.y * 255.99, .b = rgb.z * 255.99, .a = rgb.z * 255.99});
}
