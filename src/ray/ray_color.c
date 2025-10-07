/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:20:16 by yabokhar          #+#    #+#             */
/*   Updated: 2025/10/07 20:01:45 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vect3.h"
#include "ray.h"

#define T_MIN 1e-4
#define DBL_MAX 1.79769e+308
#define EPSILON 1e-4

static void	find_closest_object(const t_list *objects, t_ray r,
					t_object **current_object, double *current_t)
{
	t_object	*curr;
	double		t;

	while (objects)
	{
		curr = (t_object *)objects->content;
		t = hit_object(curr, r);
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

	if (fabs(vect3_scalar(vect3_sub(p, co->bot), co->orientation)) < EPSILON)
		return (vect3_negate(co->orientation));
	if (fabs(vect3_scalar(vect3_sub(p, co->top), co->orientation)) < EPSILON)
		return (co->orientation);
	v = vect3_sub(p, co->pos);
	d = vect3_scalar(v, co->orientation);
	normal = vect3_sub(v, vect3_const_mult(vect3_const_mult(co->orientation,
					1 + pow(co->radius / co->height, 2)), d));
	return (vect3_unit(normal));
}

static t_ray	compute_reflection_ray(t_hit rec)
{
	t_vect3	reflect_direction;
	double	cos_theta;

	cos_theta = vect3_scalar(rec.incident.direction, rec.normal);
	reflect_direction = vect3_sub(rec.incident.direction, vect3_const_mult(
				rec.normal, 2.0 * cos_theta));
	return (ray_create(vect3_add(rec.p, vect3_const_mult(
					rec.normal, T_MIN)), reflect_direction));
}

t_vect3	determine_color(t_object *closest_obj, t_context *scene,
						t_hit record, short depth)
{
	t_vect3			texture_color;
	t_ray			reflected_ray;
	t_color			reflected_color;
	t_vect3			reflected_vector;

	texture_color = color_to_vec(get_pixel_color(closest_obj, scene,
				record.p, record.normal));
	if (closest_obj->type == CHECKERBOARD && depth)
	{
		reflected_ray = compute_reflection_ray(record);
		reflected_color = ray_color(reflected_ray, scene, depth - 1);
		reflected_vector = color_to_vec(reflected_color);
		texture_color = vect3_add(vect3_const_mult(texture_color, 0.5),
				vect3_const_mult(reflected_vector, 0.5));
	}
	return (texture_color);
}

t_color	ray_color(t_ray ray, t_context *scene, short depth)
{
	t_object		*closest_obj;
	double			closest_t;
	const t_list	*objs = scene->objects;
	t_point3		p;
	t_vect3			normal;

	closest_obj = NULL;
	closest_t = DBL_MAX;
	find_closest_object(objs, ray, &closest_obj, &closest_t);
	if (!closest_obj)
		return (bg_shade(ray.direction.coords[Y]));
	if (scene->brut_mode)
		return (closest_obj->color);
	p = ray_at(ray, closest_t);
	normal = object_normal(closest_obj, p);
	if (vect3_scalar(normal, ray.direction) > 0.0)
		normal = vect3_negate(normal);
	return (vec_to_color(lightning(scene, p, normal, determine_color(
					closest_obj, scene, (t_hit){p, normal, ray}, depth))));
}
