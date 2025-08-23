/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:20:16 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/23 20:46:16 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vect3.h"
#include "ray.h"
#define DBL_MAX 1.79769e+308

t_color		ray_color(t_ray ray, t_context *scene);
static void	find_closest_object(const t_list *objects, t_ray r, \
t_object **current_object, double *current_t);

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
	else
		normal = cylinder_normal((t_cylinder *)closest_obj, ray, closest_t);
	return (vec_to_color(lightning(scene, p, normal, \
	color_to_vec(closest_obj->color))));
}

static void	find_closest_object(const t_list *objects, t_ray r, \
t_object **current_object, double *current_t)

{
	t_object	*curr;
	double		t;
	double		t2;

	while (objects)
	{
		curr = (t_object *)objects->content;
		if (curr->type == PLANE)
			t = hit_plane((t_plane *)curr, r);
		else if (curr->type == SPHERE)
			t = hit_sphere((t_sphere *)curr, r);
		else if (curr->type == CYLINDER)
		{
			t = hit_cylinder((t_cylinder *)curr, r);
			t2 = hit_cylinder_caps((t_cylinder *)curr, r);
			if (t < 0 || (t2 > T_MIN && t2 < t))
				t = t2;
		}
		if (t > T_MIN && t < *current_t)
		{
			*current_t = t;
			*current_object = curr;
		}
		objects = objects->next;
	}
}
