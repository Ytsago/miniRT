/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:20:16 by yabokhar          #+#    #+#             */
/*   Updated: 2025/09/24 16:17:49 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vect3.h"
#include "ray.h"

#define T_MIN 1e-4
#define DBL_MAX 1.79769e+308

static void	find_closest_object(const t_list *objects, t_ray r, \
t_object **current_object, double *current_t)
{
	t_object	*curr;
	double		t;

	while (objects)
	{
		curr = (t_object *)objects->content;
		if (curr->type == PLANE)
			t = hit_plane((t_plane *)curr, r);
		else if (curr->type == SPHERE)
			t = hit_sphere((t_sphere *)curr, r);
		else if (curr->type == CYLINDER)
			t = hit_cylinder((t_cylinder *)curr, r);
		else if (curr->type == CHECKERBOARD)
			t = hit_plane((t_plane *) curr, r);
		else
			t = hit_cone((t_cone *) curr, r);
		if (t > T_MIN && t < *current_t)
		{
			*current_t = t;
			*current_object = curr;
		}
		objects = objects->next;
	}
}

t_vect3	cone_normal(t_cone *co, t_point3 p)
{
	t_vect3	v;
	double	d;
	t_vect3	normal;

	v = vect3_sub(p, co->pos);
	d = vect3_scalar(v, co->orientation);
	normal = vect3_sub(v, vect3_const_mult(vect3_const_mult(co->orientation, \
						1 + pow(co->radius / co->height, 2)), d));
	return (vect3_unit(normal));
}

static t_ray	compute_reflection_ray(t_point3 p, t_vect3 normal, t_ray incident)

{
	t_vect3	reflect_direction;
	double	cos_theta;

	cos_theta = vect3_scalar(incident.direction, normal);
	reflect_direction = vect3_sub(incident.direction, vect3_const_mult(normal, 2.0 * cos_theta));
	return (ray_create(vect3_add(p, vect3_const_mult(normal, T_MIN)), reflect_direction));
}

t_color	ray_color(t_ray ray, t_context *scene)
{
	t_object		*closest_obj;
	double			closest_t;
	const t_list	*objs = scene->objects;
	t_point3		p;
	t_vect3			normal;

	t_vect3			texture_color;
	t_ray			reflected_ray;
	t_color			reflected_color;
	t_vect3			reflected_vector;

	closest_obj = NULL;
	closest_t = DBL_MAX;
	find_closest_object(objs, ray, &closest_obj, &closest_t);
	if (!closest_obj)
		return (bg_shade(ray.direction.coords[Y]));
	if (scene->brut_mode)
		return (closest_obj->color);
	p = ray_at(ray, closest_t);
	if (closest_obj->type == PLANE)
		normal = ((t_plane *)closest_obj)->orientation;
	else if (closest_obj->type == SPHERE)
		normal = vect3_unit(vect3_sub(p, closest_obj->pos));
	else if (closest_obj->type == CYLINDER)
		normal = cylinder_normal((t_cylinder *)closest_obj, ray, closest_t);
	else if (closest_obj->type == CHECKERBOARD)
		normal = ((t_plane *)closest_obj)->orientation;
	else
		normal = cone_normal((t_cone *) closest_obj, p);

	texture_color = color_to_vec(get_pixel_color(closest_obj, scene, p, normal));
	// if (closest_obj->type == CHECKERBOARD)
	{
		reflected_ray = compute_reflection_ray(p, normal, ray);
		reflected_color = ray_color(reflected_ray, scene);
		reflected_vector = color_to_vec(reflected_color);
		texture_color = vect3_add(vect3_const_mult(texture_color, 0.5), vect3_const_mult(reflected_vector, 0.5));
	}
	return (vec_to_color(lightning(scene, p, normal, texture_color)));
	/*return (vec_to_color(lightning(scene, p, normal, \
	color_to_vec(closest_obj->color))));*/
	return (get_pixel_color(closest_obj, scene, p, normal));
}
