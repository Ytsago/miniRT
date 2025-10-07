/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_mapping.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:17:44 by secros            #+#    #+#             */
/*   Updated: 2025/10/07 18:45:48 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bumpmapping.h"

static int	cylinder_part(t_cylinder *obj, double *d, t_point3 p)
{
	t_vect3	v;

	v = vect3_sub(p, obj->bot);
	*d = vect3_scalar(v, obj->orientation);
	if (*d > 0 && *d < obj->height)
		return (MIDDLE);
	else if (*d >= obj->height - EPSILON)
		return (TOP);
	else if (*d <= EPSILON)
		return (BOT);
	return (-1);
}

static t_vect3	center_mapping(t_cylinder *curr,
								t_point3 p, t_vect3 ref[2], double d)
{
	double		coord[2];
	double		local[2];
	double		teta;
	t_point3	q;
	t_vect3		to_axis;

	coord[V] = d / curr->height;
	q = vect3_add(curr->bot, vect3_const_mult(curr->orientation, d));
	to_axis = vect3_sub(p, q);
	local[X] = vect3_scalar(to_axis, ref[U]);
	local[Y] = vect3_scalar(to_axis, ref[V]);
	teta = atan2(local[X], local[Y]);
	coord[U] = (teta + M_PI) / (2 * M_PI);
	return ((t_vect3){{coord[U], coord[V]}});
}

static t_vect3	caps_mapping(t_cylinder *curr,
						t_point3 p, t_vect3 ref[2], int part)
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

static t_tbn	tbn_matrix(t_cylinder *curr,
						t_vect3 *normal, t_vect3 ref, int part)
{
	t_tbn	matrix;

	if (!part)
	{
		matrix.normal = *normal;
		matrix.bitangent = curr->orientation;
		matrix.tangent = vect3_cross(matrix.bitangent, *normal);
	}
	else
	{
		matrix.normal = *normal;
		matrix.tangent = ref;
		matrix.bitangent = vect3_cross(*normal, ref);
	}
	return (matrix);
}

t_vect3	cylinder_mapping(t_cylinder *curr, t_point3 p, t_vect3 *normal)
{
	double		d;
	const bool	part = cylinder_part(curr, &d, p);
	t_vect3		ref[2];
	t_vect3		world_up;
	t_vect3		two_d;

	world_up = (t_vect3){{0, 1, 0}};
	if (fabs(curr->orientation.y) >= 0.999)
		world_up = (t_vect3){{1, 0, 0}};
	ref[U] = vect3_unit(vect3_cross(world_up, curr->orientation));
	ref[V] = vect3_cross(curr->orientation, ref[U]);
	if (!part)
		two_d = center_mapping(curr, p, ref, d);
	else
		two_d = caps_mapping(curr, p, ref, part);
	return (set_area_value((t_object *)curr, normal,
			(double [2]){two_d.x, two_d.y},
		tbn_matrix(curr, normal, ref[U], part)));
}
