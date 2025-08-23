/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:18:33 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/23 21:17:10 by yabokhar         ###   ########.fr       */
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
	const t_vect3	ambient = \
	vect3_mult(vect3_const_mult(color_to_vec(scene->ambient_lightning.color), \
	scene->ambient_lightning.ratio), obj_color);
	const t_vect3	light_dir = \
	vect3_unit(vect3_sub(scene->lights.light_point, p));
	const double	light_dist = vect3_norm((double *)light_dir.coords);
	const t_vect3	light_color = color_to_vec(scene->lights.color);
	t_vect3			v_reflections[2];

	ft_fbzero(v_reflections, sizeof(t_vect3) * 2);
	if (!in_shadow(scene->objects, \
	(t_ray){vect3_add(p, vect3_const_mult(n, T_MIN)), light_dir}, light_dist))
	{
		v_reflections[DIFF] = vect3_mult(vect3_const_mult(light_color, \
		scene->lights.brightness_ratio * \
		fmax(vect3_scalar(n, light_dir), 0.0)), obj_color);
		v_reflections[SPEC] = vect3_const_mult(light_color, \
		scene->lights.brightness_ratio * \
		pow(fmax(vect3_scalar(n, vect3_unit(vect3_add(light_dir, \
		vect3_unit(vect3_sub(scene->camera.view_point, p))))), 0.0), 12));
	}
	return (vect3_add(vect3_add(ambient, v_reflections[DIFF]), \
	v_reflections[SPEC]));
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
		if (curr->type == CYLINDER)
		{
			t = hit_cylinder((t_cylinder *) curr, ray);
			if (t > -1 && t < max_dist)
				return (true);
		}
		objs = objs->next;
	}
	return (false);
}
