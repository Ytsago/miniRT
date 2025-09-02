/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:18:09 by secros            #+#    #+#             */
/*   Updated: 2025/09/02 18:39:27 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>
#include "ray.h"

#define U 0
#define V 1

t_vect3	apply_tbn(t_tbn tbn, t_vect3 normal)
{
	t_vect3	result;

	result.x = tbn.tangent.x * normal.x + \
			tbn.bitangent.x * normal.y + \
			tbn.normal.x * normal.z;
	result.y = tbn.tangent.y * normal.x + \
			tbn.bitangent.y * normal.y +\
			tbn.normal.y * normal.z;
	result.z = tbn.tangent.z * normal.x + \
			tbn.bitangent.z * normal.y +\
			tbn.normal.z * normal.z;
	return (vect3_unit(result));
}

t_vect3	get_normal_map(t_pict *map, double u, double v)
{
	t_vect3		normal;

	normal = color_to_vec(coord_to_img(map, u, v));
	normal = vect3_const_mult(normal, 2);
	normal = vect3_add(normal, (t_vect3) {{-1, -1, -1}});
	return (vect3_unit(normal));
}

t_tbn	compute_sphere_tbn(double u, double v, t_vect3 normal)
{
	t_tbn	sp_tbn;

	sp_tbn.tangent = (t_vect3) {{-sin(2 * M_PI * u), 0, cos(2 * M_PI * u)}};
	sp_tbn.tangent = vect3_unit(sp_tbn.tangent);
	sp_tbn.bitangent = (t_vect3) {{-cos(2 * M_PI * u) * sin(M_PI * v), \
		cos(M_PI * v), -sin(2 * M_PI * u) * sin(M_PI * v)}};
	sp_tbn.bitangent = vect3_unit(sp_tbn.bitangent);
	sp_tbn.normal = normal;
	return (sp_tbn);
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
		*normal = apply_tbn(compute_sphere_tbn(u, v, *normal), \
					  get_normal_map(obj->texture[1], u, v));
	if (obj->texture[0])
		return (color_to_vec(coord_to_img(obj->texture[0], u, v)));
	return (color_to_vec(obj->color)); //duplicated in get_pixel_color
}

t_tbn	compute_plane_tbn(t_vect3 axis_u, t_vect3 axis_v,t_vect3 normal)
{
	t_tbn	pl_tbn;

	pl_tbn.normal = normal;
	pl_tbn.tangent = axis_u;
	pl_tbn.bitangent = axis_v;
	return (pl_tbn);
}

t_vect3	plane_mapping(t_object *obj, t_point3 p, t_vect3 *normal)
{
	t_vect3	axis[2];
	t_vect3	to_point;
	t_vect3	tmp;
	double	u;
	double	v;

	tmp = (t_vect3) {{1, 0, 0}};
	if (fabs(vect3_scalar(*normal, tmp)) > 0.9)
		tmp = (t_vect3) {{0, 1, 0}};
	axis[V] = vect3_unit(vect3_cross(*normal, tmp));
	axis[U] = vect3_cross(*normal, axis[V]);
	to_point = vect3_sub(p, obj->pos);
	u = fmod(vect3_scalar(to_point, axis[U]) / 5, 1.0);
	v = fmod(vect3_scalar(to_point, axis[V]) / 5, 1.0);
	if (u < 0.0)
		u += 1.0;
	if (v < 0.0)
		v += 1.0;
	if (obj->texture[1])
		*normal = apply_tbn(compute_plane_tbn(axis[U], axis[V], *normal), \
					  get_normal_map(obj->texture[1], u, v));
	if (obj->texture[0])
		return (color_to_vec(coord_to_img(obj->texture[0], u, v)));
	return (color_to_vec(obj->color));
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
	if (obj->type == PLANE)
		texture = plane_mapping(obj, p, &normal);
	return (vec_to_color(lightning(scene, p, normal, texture)));
}
