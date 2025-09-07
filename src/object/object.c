/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:00:47 by secros            #+#    #+#             */
/*   Updated: 2025/09/04 16:01:06 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "miniRT.h"

double	hit_object(t_object *obj, t_ray r)
{
	if (obj->type == PLANE)
		return (hit_plane((t_plane *) obj, r));
	if (obj->type == SPHERE)
		return (hit_sphere((t_sphere *) obj, r));
	if (obj->type == CYLINDER)
		return (hit_cylinder((t_cylinder *) obj, r));
	if (obj->type == CONE)
		return (hit_cone((t_cone *) obj, r));
	return (-1);
}

