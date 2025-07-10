/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:20:16 by yabokhar          #+#    #+#             */
/*   Updated: 2025/07/09 20:20:04 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vect3.h"
#include "ray.h"
#define SHININESS 50
#define DBL_MAX 1.79769e+308

t_vect3	background_shade(void)
{
	t_color c;
	c.r = 199;
	c.g = 193,
	c.b = 221;
	return (color_to_vec(c));
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
		objs = objs->next;
	}
	return (false);
}

t_vect3	get_light_dir(t_point3 light_point, t_point3 ray_point)
{
	return (vect3_unit(vect3_sub(light_point, ray_point)));
}

t_vect3	lighting(t_context *scene, t_point3 p, t_vect3 n, t_color obj_color)
{
	const t_vect3	v_obj_color = color_to_vec(obj_color);
	const t_vect3	v_amb_light = color_to_vec(scene->ambient_lightning.color);
	const t_vect3	ambient = vect3_mult(vect3_const_mult(v_amb_light, scene->ambient_lightning.ratio), v_obj_color);
	t_vect3	light_dir = vect3_unit(vect3_sub(scene->light.light_point, p));
	double	light_dist = vect3_norm(light_dir.coords);
	const t_ray		shadow_ray = (t_ray){vect3_add(p, vect3_const_mult(n, T_MIN)), light_dir};
	const t_vect3	light_color = color_to_vec(scene->light.color);
	t_vect3			v_reflections[2];
	double			reflections[2];

	ft_fbzero(v_reflections, sizeof(t_vect3) * 2);
	if (!in_shadow(scene, shadow_ray, light_dist))
	{
		reflections[DIFF] = fmax(vect3_scalar(n, light_dir), 0.0);
        v_reflections[DIFF] = vect3_mult(vect3_const_mult(light_color, scene->light.brightness_ratio * reflections[DIFF]), v_obj_color);
        t_vect3 view_dir = vect3_unit(vect3_sub(scene->camera.view_point, p));
        t_vect3 halfway_dir = vect3_unit(vect3_add(light_dir, view_dir));
        reflections[SPEC] = pow(fmax(vect3_scalar(n, halfway_dir), 0.0), SHININESS);
        v_reflections[SPEC] = vect3_const_mult(light_color, scene->light.brightness_ratio * reflections[SPEC]);
	}
	return (vect3_add(vect3_add(ambient, v_reflections[DIFF]), v_reflections[SPEC]));
}

void	find_closest_sp(const t_list *o, t_ray r, t_object **c_obj, double *c_t)
{
	t_object	*curr;
	double		t;

	while (o)
	{
		curr = (t_object *)o->content;
		if (curr->type == SPHERE)
		{
			t = hit_sphere((t_sphere *)curr, r);
		}
		else if (curr->type == PLANE)
			t = hit_plane((t_plane *)curr, r);
		else
			t = hit_cylinder((t_cylinder *)curr, r);
		if (t > T_MIN && t < *c_t)
		{
			*c_t = t;
			*c_obj = curr;
		}
		o = o->next;
	}
}

t_vect3	cylinder_normal(t_cylinder *cy, t_vect3 p)
{
	const t_vect3	w = vect3_sub(p, cy->pos);
	const double	t = vect3_scalar(w, cy->orientation);
	const t_vect3	q = vect3_add(cy->pos, vect3_const_mult(cy->orientation, t));
	
	return (vect3_unit(vect3_sub(p, q)));
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
	find_closest_sp(objs, ray, &closest_obj, &closest_t);
	if (closest_obj)
	{
		if (scene->spectator_mode)
			return (closest_obj->color);
		p = ray_at(ray, closest_t);
		if (closest_obj->type == SPHERE)
			normal = vect3_unit(vect3_sub(p, closest_obj->pos));
		else if (closest_obj->type == PLANE)
			normal = ((t_plane *)closest_obj)->orientation;
		else if (closest_obj->type == CYLINDER)
			normal = cylinder_normal((t_cylinder *)closest_obj, p);
		else
			return ((t_color) {0});
		if (vect3_scalar(ray.direction, normal) > 0)
			normal = vect3_negate(normal);
		return (vec_to_color(lighting(scene, p, normal, closest_obj->color)));
	}
	return (vec_to_color(background_shade()));
}
