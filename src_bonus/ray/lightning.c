/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:18:33 by yabokhar          #+#    #+#             */
/*   Updated: 2025/10/08 15:53:18 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vect3.h"
#include "ray.h"

#define VIEW 0
#define HALFWAY 1
#define DIFF 0
#define SPEC 1
#define RESULT 0
#define DIR 1
#define COLOR 2
#define T_MIN 1e-4
#define EPSILON 1e-6

t_vect3		lightning(t_context *scene, \
t_point3 p, t_vect3 n, t_vect3 obj_color);
static bool	in_shadow(const t_list *objs, t_ray ray, double max_dist);

static void	get_lights_data(t_light *cur, t_vect3 l_data[3], \
double *l_dist, t_point3 p)

{
	l_data[DIR] = vect3_sub(cur->light_point, p);
	*l_dist = vect3_norm((double *)l_data[DIR].coords);
	l_data[DIR] = vect3_unit(l_data[DIR]);
	l_data[COLOR] = color_to_vec(cur->color);
}

t_vect3	get_diff(t_vect3 l_data[3], t_light *l, t_vect3 n, t_vect3 obj_color)

{
	return (vect3_mult(\
vect3_const_mult(l_data[COLOR], \
l->brightness_ratio * fmax(vect3_scalar(n, l_data[DIR]), 0.0)), \
obj_color));
}

double	r_times_v(t_vect3 n, t_vect3 l_dir, t_vect3 cam_view_point, t_point3 p)

{
	return (fmax(vect3_scalar(n, vect3_unit(vect3_add(l_dir, \
vect3_unit(vect3_sub(cam_view_point, p))))), 0.0));
}

t_vect3	lightning(t_context *scene, t_point3 p, t_vect3 n, t_vect3 obj_c)
{
	t_list			*l_node;
	t_light			*cur_light;
	t_vect3			l_data[3];
	double			light_dist;
	t_vect3			reflect_v[2];

	nullify_vectors(l_data, reflect_v);
	l_data[RESULT] = initial_light(scene->ambient_lightning, obj_c);
	l_node = scene->lights_list;
	while (l_node)
	{
		cur_light = l_node->content;
		get_lights_data(l_node->content, l_data, &light_dist, p);
		if (!in_shadow(scene->objects, \
	(t_ray){vect3_add(p, vect3_const_mult(n, T_MIN)), l_data[DIR]}, light_dist))
		{
			reflect_v[DIFF] = get_diff(l_data, l_node->content, n, obj_c);
			reflect_v[SPEC] = vect3_const_mult(l_data[COLOR], \
cur_light->brightness_ratio * \
pow(r_times_v(n, l_data[DIR], scene->camera.view_point, p), 42));
			add_reflections(&l_data[RESULT], reflect_v);
		}
		l_node = l_node->next;
	}
	return (l_data[RESULT]);
}

static bool	in_shadow(const t_list *objs, t_ray ray, double max_dist)
{
	t_object		*curr;
	double			t;

	while (objs)
	{
		curr = (t_object *)objs->content;
		t = hit_object(curr, ray);
		if (t > T_MIN && t < max_dist)
			return (true);
		objs = objs->next;
	}
	return (false);
}
