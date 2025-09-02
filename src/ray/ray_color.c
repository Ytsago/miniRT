/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:20:16 by yabokhar          #+#    #+#             */
/*   Updated: 2025/09/02 11:29:26 by secros           ###   ########.fr       */
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
	double		t[2];

	while (objects)
	{
		curr = (t_object *)objects->content;
		if (curr->type == PLANE)
			t[0] = hit_plane((t_plane *)curr, r);
		else if (curr->type == SPHERE)
			t[0] = hit_sphere((t_sphere *)curr, r);
		else
			t[0] = hit_cylinder((t_cylinder *)curr, r);
		if (t[0] > T_MIN && t[0] < *current_t)
		{
			*current_t = t[0];
			*current_object = curr;
		}
		objects = objects->next;
	}
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
	else
		normal = cylinder_normal((t_cylinder *)closest_obj, ray, closest_t);
	/*return (vec_to_color(lightning(scene, p, normal, \
	color_to_vec(closest_obj->color))));*/
	return (get_pixel_color(closest_obj, scene, p, normal));
}
