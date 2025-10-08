/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:44:22 by secros            #+#    #+#             */
/*   Updated: 2025/10/08 15:53:01 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bumpmapping.h"

#define L 0
#define TETA 1

static int	find_part(t_cone *obj, t_vect3 p, double *d)
{
	t_vect3	apex_to_p;

	apex_to_p = vect3_sub(p, obj->pos);
	*d = vect3_scalar(apex_to_p, obj->orientation);
	if (*d >= obj->height / 2 - EPSILON)
		return (TOP);
	else if (*d <= -obj->height / 2 + EPSILON)
		return (BOT);
	else if (*d < obj->height / 2 && *d > -obj->height / 2)
		return (MIDDLE);
	return (-1);
}

static t_vect3	center_mapping(t_cone *curr, t_vect3 ref[2],
							t_point3 p, double d)
{
	double		coord[2];
	double		local[2];
	double		teta;
	t_point3	q;
	t_vect3		to_axis;

	coord[V] = vect3_norm(vect3_sub(p, curr->pos).coords)
		/ (sqrt(pow(curr->height, 2) + pow(curr->radius, 2)));
	q = vect3_add(curr->pos, vect3_const_mult(curr->orientation, d));
	to_axis = vect3_sub(p, q);
	local[X] = vect3_scalar(to_axis, ref[U]);
	local[Y] = vect3_scalar(to_axis, ref[V]);
	teta = atan2(local[U], local[V]);
	coord[U] = (teta + M_PI) / (2 * M_PI);
	return ((t_vect3){{coord[U], coord[V]}});
}

static t_vect3	caps_mapping(t_cone *curr, t_vect3 ref[2], t_point3 p, int part)
{
	double	local[2];
	double	coord[2];
	t_vect3	vcap;

	if (part == 1)
		vcap = vect3_sub(p, curr->top);
	else
		vcap = vect3_sub(p, curr->bot);
	local[X] = vect3_scalar(vcap, ref[U]);
	local[Y] = vect3_scalar(vcap, ref[V]);
	coord[U] = local[X] / (curr->radius * 2) + 0.5;
	coord[V] = local[Y] / (curr->radius * 2) + 0.5;
	return ((t_vect3){{coord[U], coord[V]}});
}

static t_tbn	tbn_matrix(t_vect3 *normal, t_vect3 ref[2], int part)
{
	t_tbn	matrix;

	if (!part)
	{
		matrix.normal = *normal;
		matrix.tangent = ref[V];
		matrix.bitangent = vect3_cross(matrix.normal, matrix.tangent);
	}
	else
	{
		matrix.normal = *normal;
		matrix.tangent = ref[U];
		matrix.bitangent = vect3_cross(*normal, ref[U]);
	}
	return (matrix);
}

t_vect3	cone_mapping(t_cone *curr, t_point3 p, t_vect3 *normal)
{
	double		d;
	const bool	part = find_part(curr, p, &d);
	t_vect3		ref[2];
	t_vect3		world_up;
	t_vect3		two_d;

	world_up = (t_vect3){{0, 1, 0}};
	if (fabs(curr->orientation.y) >= 0.999)
		world_up = (t_vect3){{1, 0, 0}};
	ref[U] = vect3_unit(vect3_cross(world_up, curr->orientation));
	ref[V] = vect3_cross(curr->orientation, ref[U]);
	if (!part)
		two_d = center_mapping(curr, ref, p, d);
	else
		two_d = caps_mapping(curr, ref, p, part);
	return (set_area_value((t_object *)curr, normal,
			(double [2]){two_d.x, two_d.y}, tbn_matrix(normal, ref, part)));
}
