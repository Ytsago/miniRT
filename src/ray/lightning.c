/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:18:33 by yabokhar          #+#    #+#             */
/*   Updated: 2025/09/02 11:46:30 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vect3.h"
#include "ray.h"

#define VIEW 0
#define HALFWAY 1
#define DIFF 0
#define SPEC 1
#define T_MIN 1e-4
#define EPSILON 1e-6

t_vect3		lightning(t_context *scene, \
t_point3 p, t_vect3 n, t_vect3 obj_color);
static bool	in_shadow(const t_list *objs, t_ray ray, double max_dist);

t_vect3	lightning(t_context *scene, t_point3 p, t_vect3 n, t_vect3 obj_color)
{
	t_vect3			total_lightning;
	t_list			*light;
	t_light			*current_light;
	t_vect3			light_dir;
	double			light_dist;
	t_vect3			light_color;
	t_vect3			v_reflections[2];

	ft_fbzero(v_reflections, sizeof(t_vect3) * 2);
	total_lightning = vect3_mult(vect3_const_mult(color_to_vec(\
	scene->ambient_lightning.color), \
	scene->ambient_lightning.ratio), obj_color);
	light = scene->lights_list;
	while (light)
	{
		current_light = light->content;
		light_dir = vect3_unit(vect3_sub(current_light->light_point, p));
		light_dist = vect3_norm((double *)light_dir.coords); 
		light_color = color_to_vec(current_light->color);
		if (!in_shadow(scene->objects, \
		(t_ray){vect3_add(p, vect3_const_mult(n, T_MIN)), light_dir}, light_dist))
		{
			v_reflections[DIFF] = vect3_mult(vect3_const_mult(light_color, \
			current_light->brightness_ratio * \
			fmax(vect3_scalar(n, light_dir), 0.0)), obj_color);
			v_reflections[SPEC] = vect3_const_mult(light_color, \
			current_light->brightness_ratio * \
			pow(fmax(vect3_scalar(n, vect3_unit(vect3_add(light_dir, \
			vect3_unit(vect3_sub(scene->camera.view_point, p))))), 0.0), 42));
			total_lightning = vect3_add(total_lightning, v_reflections[DIFF]);
			total_lightning = vect3_add(total_lightning, v_reflections[SPEC]);
		}
		light = light->next;
	}
	return (total_lightning);
}

static bool	in_shadow(const t_list *objs, t_ray ray, double max_dist)

{
	t_object		*curr;
	double			t;

	while (objs)
	{
		curr = (t_object *)objs->content;
		if (curr->type == SPHERE)
		{
			t = hit_sphere((t_sphere *) curr, ray);
			if (t > T_MIN && t < max_dist)
				return (true);
		}
		if (curr->type == PLANE)
		{
			t = hit_plane((t_plane *) curr, ray);
			if (t > T_MIN && t < max_dist)
				return (true);
		}
		if (curr->type == CYLINDER)
		{
			t = hit_cylinder((t_cylinder *) curr, ray);
			if (t > T_MIN && t < max_dist)
				return (true);
		}
		objs = objs->next;
	}
	return (false);
}
