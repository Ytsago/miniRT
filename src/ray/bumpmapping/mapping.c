/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:47:41 by secros            #+#    #+#             */
/*   Updated: 2025/10/08 15:50:25 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bumpmapping.h"

t_vect3	apply_tbn(t_tbn tbn, t_vect3 normal)
{
	t_vect3	result;

	result.x = tbn.tangent.x * normal.x
		+ tbn.bitangent.x * normal.y
		+ tbn.normal.x * normal.z;
	result.y = tbn.tangent.y * normal.x
		+ tbn.bitangent.y * normal.y
		+ tbn.normal.y * normal.z;
	result.z = tbn.tangent.z * normal.x
		+ tbn.bitangent.z * normal.y
		+ tbn.normal.z * normal.z;
	return (vect3_unit(result));
}

t_vect3	get_normal_map(t_pict *map, double u, double v)
{
	t_vect3		normal;

	normal = color_to_vec(coord_to_img(map, u, v));
	normal = vect3_const_mult(normal, 2);
	normal = vect3_add(normal, (t_vect3){{-1, -1, -1}});
	return (vect3_unit(normal));
}

t_vect3	set_area_value(t_object *obj, t_vect3 *normal, \
						double value[2], t_tbn matrix)
{
	if (obj->text->img[1])
		*normal = apply_tbn(matrix, get_normal_map(obj->text->img[1], \
value[U], value[V]));
	if (obj->text->img[0])
		return (color_to_vec(coord_to_img(obj->text->img[0], value[U], \
value[V])));
	else
		return (color_to_vec(obj->text->based));
}

t_color	get_pixel_color(t_object *obj, t_context *scene, \
						t_point3 p, t_vect3 normal)
{
	t_vect3	texture;

	if (obj->type == SPHERE && obj->text)
		texture = sphere_mapping(obj, p, &normal);
	else if (obj->type == PLANE && obj->text)
		texture = plane_mapping(obj, p, &normal);
	else if (obj->type == CYLINDER && obj->text)
		texture = cylinder_mapping((t_cylinder *)obj, p, &normal);
	else if (obj->type == CHECKERBOARD)
		texture = checkerboard_mapping(obj, p, &normal);
	else if (obj->type == CONE && obj->text)
		texture = cone_mapping((t_cone *)obj, p, &normal);
	else
		texture = color_to_vec(obj->color);
	return (vec_to_color(lightning(scene, p, normal, texture)));
}
