/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:20:16 by yabokhar          #+#    #+#             */
/*   Updated: 2025/09/01 15:07:14 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vect3.h"
#include "ray.h"

#define T_MIN 1e-4
#define DBL_MAX 1.79769e+308

t_color		ray_color(t_ray ray, t_context *scene);
static void	find_closest_object(const t_list *objects, t_ray r, \
t_object **current_object, double *current_t);

t_vect3	get_normal_map(t_pict *map, double u, double v)
{
	const int	pixel_x = u * map->size[0];
	const int	pixel_y = v * map->size[1];
	t_color		c_normal;
	t_vect3		normal;

	c_normal.color = ((unsigned int ) \
		map->addr[pixel_y * map->l_size + pixel_x * (map->bbp / 8)]);
	normal = color_to_vec(c_normal);
	normal = vect3_const_mult(normal, 2);
	normal = vect3_add(normal, (t_vect3) {{-1, -1, -1}});
	return (vect3_unit(normal));
}

t_vect3	get_texture(t_pict *map, double u, double v)
{
	const int	pixel_x = u * map->size[0];
	const int	pixel_y = v * map->size[1];
	t_color		p_color;

	p_color.color = ((unsigned int ) \
		map->addr[pixel_y * map->l_size + (pixel_x * map->bbp / 8)]);
	return (color_to_vec(p_color));
}

t_vect3	sphere_mapping(t_object *obj, t_point3 p, t_vect3* normal)
{
	double	u;
	double	v;
	t_vect3	to_center;

	to_center = vect3_sub(p, obj->pos);
	to_center = vect3_const_div(to_center, ((t_sphere *)obj)->radius);
	/*u = acos(to_center.y) / M_PI;
	v = (atan2(to_center.x, to_center.z) + M_PI) / (2 * M_PI);*/
	u = 0.5 + atan2(to_center.z, to_center.x) / (2 * M_PI);
	v = 0.5 - asin(to_center.y) / M_PI;
	if (obj->texture[1])
		*normal = get_normal_map(obj->texture[1], u, v);
	if (obj->texture[0])
		return (get_texture(obj->texture[0], u, v));
	return (color_to_vec(obj->color)); //duplicated in get_pixel_color
}

t_color	get_pixel_color(t_object *obj, t_context *scene, \
	t_point3 p, t_vect3 normal)
{
	t_vect3	texture;

	texture = color_to_vec(obj->color); //May be removed for performance
	if (!obj->texture[0] && !obj->texture[1])
		return (vec_to_color(lightning(scene, p, normal, texture))); 
	if (obj->type == SPHERE)
		texture = sphere_mapping(obj, p, &normal);
	return (vec_to_color(lightning(scene, p, normal, texture)));
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
		{
			t[0] = hit_cylinder((t_cylinder *)curr, r);
			t[1] = hit_cylinder_caps((t_cylinder *)curr, r);
			if (t[0] < 0 || (t[1] > T_MIN && t[1] < t[0]))
				t[0] = t[1];
		}
		if (t[0] > T_MIN && t[0] < *current_t)
		{
			*current_t = t[0];
			*current_object = curr;
		}
		objects = objects->next;
	}
}
