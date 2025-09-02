/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:18:09 by secros            #+#    #+#             */
/*   Updated: 2025/09/02 11:07:57 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vect3	get_normal_map(t_pict *map, double u, double v)
{
	t_vect3		normal;

	normal = color_to_vec(coord_to_img(map, u, v));
	normal = vect3_const_mult(normal, 2);
	normal = vect3_add(normal, (t_vect3) {{-1, -1, -1}});
	return (vect3_unit(normal));
}

t_vect3	sphere_mapping(t_object *obj, t_point3 p, t_vect3* normal)
{
	double	u;
	double	v;
	t_vect3	to_center;

	to_center = vect3_sub(p, obj->pos);
	to_center = vect3_const_div(to_center, ((t_sphere *)obj)->radius);
	u = 0.5 + atan2(to_center.z, to_center.x) / (2 * M_PI);
	v = 0.5 - asin(to_center.y) / M_PI;
	if (obj->texture[1])
		*normal = get_normal_map(obj->texture[1], u, v);
	if (obj->texture[0])
		return (color_to_vec(coord_to_img(obj->texture[0], u, v)));
	return (color_to_vec(obj->color)); //duplicated in get_pixel_color
}

t_color	get_pixel_color(t_object *obj, t_context *scene, \
	t_point3 p, t_vect3 normal)
{
	t_vect3	texture;

	texture = color_to_vec(obj->color); //May be removed for performance
	if (!obj->texture[0] && !obj->texture[1])
		return (vec_to_color(lightning(scene, p, normal, texture))); 
	if (obj->type == SPHERE)
		texture = sphere_mapping(obj, p, &normal);
	return (vec_to_color(lightning(scene, p, normal, texture)));
}
