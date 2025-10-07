/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:17:50 by secros            #+#    #+#             */
/*   Updated: 2025/10/07 17:26:27 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bumpmapping.h"

static t_tbn	tbn_matrix(double u, double v, t_vect3 normal)
{
	t_tbn	sp_tbn;

	sp_tbn.tangent = (t_vect3){{-sin(2 * M_PI * u), 0, cos(2 * M_PI * u)}};
	sp_tbn.tangent = vect3_unit(sp_tbn.tangent);
	sp_tbn.bitangent = (t_vect3){{-cos(2 * M_PI * u) * sin(M_PI * v), \
cos(M_PI * v), -sin(2 * M_PI * u) * sin(M_PI * v)}};
	sp_tbn.bitangent = vect3_unit(sp_tbn.bitangent);
	sp_tbn.normal = normal;
	return (sp_tbn);
}

t_vect3	sphere_mapping(t_object *obj, t_point3 p, t_vect3 *normal)
{
	double	u;
	double	v;
	t_vect3	to_center;

	to_center = vect3_sub(p, obj->pos);
	to_center = vect3_const_div(to_center, ((t_sphere *)obj)->radius);
	u = 0.5 + atan2(to_center.z, to_center.x) / (2 * M_PI);
	v = 0.5 - asin(to_center.y) / M_PI;
	return (set_area_value(obj, normal, (double [2]){u, v}, \
tbn_matrix(u, v, *normal)));
}
