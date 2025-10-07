/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_mapping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:17:09 by secros            #+#    #+#             */
/*   Updated: 2025/10/07 18:48:24 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bumpmapping.h"

static t_tbn	tbn_matrix(t_vect3 axis_u, t_vect3 axis_v, t_vect3 normal)
{
	t_tbn	pl_tbn;

	pl_tbn.normal = normal;
	pl_tbn.tangent = axis_u;
	pl_tbn.bitangent = axis_v;
	return (pl_tbn);
}

t_vect3	plane_mapping(t_object *obj, t_point3 p, t_vect3 *normal)
{
	t_vect3	axis[2];
	t_vect3	to_point;
	t_vect3	tmp;
	double	u;
	double	v;

	tmp = (t_vect3){{1, 0, 0}};
	if (fabs(vect3_scalar(*normal, tmp)) > 0.9)
		tmp = (t_vect3){{0, 1, 0}};
	axis[V] = vect3_unit(vect3_cross(*normal, tmp));
	axis[U] = vect3_cross(*normal, axis[V]);
	to_point = vect3_sub(p, obj->pos);
	u = fmod(vect3_scalar(to_point, axis[U]) / 5, 1.0);
	v = fmod(vect3_scalar(to_point, axis[V]) / 5, 1.0);
	if (u < 0.0)
		u += 1.0;
	if (v < 0.0)
		v += 1.0;
	return (set_area_value(obj, normal, (double [2]){u, v},
		tbn_matrix(axis[U], axis[V], *normal)));
}
