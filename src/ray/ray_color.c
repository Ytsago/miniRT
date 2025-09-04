/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:20:16 by yabokhar          #+#    #+#             */
/*   Updated: 2025/09/04 14:54:34 by secros           ###   ########.fr       */
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

t_color	ray_color(t_ray ray, t_context *scene)
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
	if (closest_obj->type == PLANE)
		normal = ((t_plane *)closest_obj)->orientation;
	else if (closest_obj->type == SPHERE)
		normal = vect3_unit(vect3_sub(p, closest_obj->pos));
	else if (closest_obj->type == CYLINDER)
		normal = cylinder_normal((t_cylinder *)closest_obj, ray, closest_t);
	else
		normal = cone_normal((t_cone *) closest_obj, p);
	/*return (vec_to_color(lightning(scene, p, normal, \
	color_to_vec(closest_obj->color))));*/
	return (get_pixel_color(closest_obj, scene, p, normal));
}
