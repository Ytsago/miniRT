/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:18:33 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/23 20:47:03 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vect3.h"
#include "ray.h"

t_vect3	lightning(t_context *scene, t_point3 p, t_vect3 n, t_vect3 obj_color);
bool	in_shadow(t_context *scene, t_ray ray, double max_dist);

t_vect3	lightning(t_context *scene, t_point3 p, t_vect3 n, t_vect3 obj_color)
{
	const t_vect3	v_amb_light = color_to_vec(scene->ambient_lightning.color);
	const t_vect3	ambient = vect3_mult(vect3_const_mult(v_amb_light, scene->ambient_lightning.ratio), obj_color);
	t_vect3	light_dir = vect3_unit(vect3_sub(scene->lights.light_point, p));
	double	light_dist = vect3_norm(light_dir.coords);
	const t_ray		shadow_ray = (t_ray){vect3_add(p, vect3_const_mult(n, T_MIN)), light_dir};
	const t_vect3	light_color = color_to_vec(scene->lights.color);
	t_vect3			v_reflections[2];
	double			reflections[2];

	ft_fbzero(v_reflections, sizeof(t_vect3) * 2);
	if (!in_shadow(scene, shadow_ray, light_dist))
	{
		reflections[DIFF] = fmax(vect3_scalar(n, light_dir), 0.0);
        v_reflections[DIFF] = vect3_mult(vect3_const_mult(light_color, scene->lights.brightness_ratio * reflections[DIFF]), obj_color);
        t_vect3 view_dir = vect3_unit(vect3_sub(scene->camera.view_point, p));
        t_vect3 halfway_dir = vect3_unit(vect3_add(light_dir, view_dir));
        reflections[SPEC] = pow(fmax(vect3_scalar(n, halfway_dir), 0.0), 12);
        v_reflections[SPEC] = vect3_const_mult(light_color, scene->lights.brightness_ratio * reflections[SPEC]);
	}
	return (vect3_add(vect3_add(ambient, v_reflections[DIFF]), v_reflections[SPEC]));
}

bool	in_shadow(t_context *scene, t_ray ray, double max_dist)

{
	const t_list	*objs = scene->objects;
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
		if (curr->type == CYLINDER) {
			t = hit_cylinder((t_cylinder *) curr, ray);
			if (t > -1 && t < max_dist)
				return (true);
		}
		objs = objs->next;
	}
	return (false);
}
