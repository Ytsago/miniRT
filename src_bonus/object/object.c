/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:00:47 by secros            #+#    #+#             */
/*   Updated: 2025/10/06 21:39:12 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "miniRT.h"

double	hit_object(t_object *obj, t_ray r)
{
	if (obj->type == PLANE)
		return (hit_plane((t_plane *) obj, r));
	else if (obj->type == SPHERE)
		return (hit_sphere((t_sphere *) obj, r));
	else if (obj->type == CYLINDER)
		return (hit_cylinder((t_cylinder *) obj, r));
	else if (obj->type == CONE)
		return (hit_cone((t_cone *) obj, r));
	else if (obj->type == CHECKERBOARD)
		return (hit_plane((t_plane *) obj, r));
	return (-1);
}

t_vect3	object_normal(t_object *obj, t_vect3 p)
{
	t_vect3	normal;

	if (obj->type == PLANE)
		normal = ((t_plane *)obj)->orientation;
	else if (obj->type == SPHERE)
		normal = vect3_unit(vect3_sub(p, obj->pos));
	else if (obj->type == CYLINDER)
		normal = cylinder_normal((t_cylinder *)obj, p);
	else if (obj->type == CHECKERBOARD)
		normal = ((t_plane *)obj)->orientation;
	else
		normal = cone_normal((t_cone *) obj, p);
	return (normal);
}
