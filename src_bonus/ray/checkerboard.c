/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:50:38 by secros            #+#    #+#             */
/*   Updated: 2025/10/07 17:55:06 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

#define U 0
#define V 1

static void	compute_uv_axes(t_vect3 normal, t_vect3 *axis_u, t_vect3 *axis_v)
{
	t_vect3	tmp;
	t_vect3	v;

	tmp = (t_vect3){{1, 0, 0}};
	if (fabs(vect3_scalar(normal, tmp)) > 0.9)
		tmp = (t_vect3){{0, 1, 0}};
	v = vect3_unit(vect3_cross(normal, tmp));
	*axis_v = v;
	*axis_u = vect3_cross(normal, v);
}

t_vect3	checkerboard_mapping(t_object *obj, t_point3 p, t_vect3 *normal)
{
	t_plane	*pl;
	t_vect3	axis[2];
	t_vect3	to_point;
	double	d[2];

	pl = (t_plane *)obj;
	compute_uv_axes(*normal, &axis[U], &axis[V]);
	to_point = vect3_sub(p, pl->pos);
	d[U] = vect3_scalar(to_point, axis[U]) / 1.0;
	d[V] = vect3_scalar(to_point, axis[V]) / 1.0;
	if ((((long)floor(d[U]) + (long)floor(d[V])) % 2) == 0)
		return (color_to_vec((t_color){.r = 255, .g = 255, .b = 255, .a = 0}));
	return (color_to_vec((t_color){.r = 0, .g = 0, .b = 0, .a = 0}));
}
